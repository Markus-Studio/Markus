# Markus Layers IR

## Summary

| Property           | List  | Index | GroupBy | Aggregation | Map   |
| ------------------ | ----- | ----- | ------- | ----------- | ----- |
| aggregation        | **T** |       | **T**   |             |       |
| axis               |       |       | **T**   |             |       |
| axisSorted         |       |       | **T**   |             |       |
| dynamicFilter      | **T** |       |         |             | **T** |
| dynamicLabelFilter |       |       | **T**   |             |       |
| function           |       | **T** |         | **T**       |       |
| parameters         |       |       |         |             | **T** |
| selected           | **T** |       |         |             |       |
| sortedAxises       | **T** |       |         |             |       |
| staticFilter       | **T** |       | **T**   | **T**       | **T** |
| subject            |       |       |         | **T**       |       |

## Examples

---

### Static List

```markus
query {
  f()
}
```

Layers Chain:

```
List{staticFilter: f}
```

---

### Dynamic List

```markus
query {
  g(x, y)
}
```

Layers Chain:

```
# g(x, y) = f() ∩ h(x) ∩ p(x, y); where `h` is indexable.
Index{function: h}
List{staticFilter: f, dynamicFilter: p}
```

---

### Static Aggregation

```markus
query {
  f(),
  sum(.x)
}
```

Layers Chain:

```
Aggregation{staticFilter: f, function: sum, subject: .x}
```

---

### Dynamic Aggregation

```markus
query {
  g(x, y),
  sum(.x)
}
```

Layers Chain:

```
# g(x, y) = f() ∩ p(x, y)
Map{parameters: [x, y], dynamicFilter: p, staticFilter: f}
Aggregation{function: sum, subject: .x}
```

Optimized for Memory:

```
List{
  staticFilter: f,
  dynamicFilter: p,
  aggregation: Aggregation{
    function: sum,
    subject: .x
  }
}
```

---

### Simple Static GroupBy

```markus
query {
  f(),
  groupBy(.a)
}
```

Layers Chain:

```
GroupBy{axis: .a, staticFilter: f}
List{}
```

---

### Simple Dynamic GroupBy

```markus
query {
  g(x, y),
  groupBy(.a)
}
```

Layers Chain:

```
# g(x, y) = f() ∩ h(x) ∩ p(x, y) ∩ u(y); where `h` is indexable.
# and `u` is filtering `.a`
GroupBy{axis: .a, staticFilter: f, dynamicLabelFilter: u}
Index{function: h} # If h is not empty.
List{dynamicFilter: p}
```

---

### Aggregated Static GroupBy

```markus
query {
  f(),
  groupBy(.a, {
    sum(.x)
  })
}
```

Layers Chain:

```
GroupBy{axis: .a, staticFilter: f}
Aggregation{function: sum, subject: .x}
```

---

### Aggregated Dynamic GroupBy

```markus
query {
  g(x, y, z),
  groupBy(.a, {
    sum(.x)
  })
}
```

Layers Chain:

```
# g(x, y, z) = f() ∩ p(x, y) ∩ u(z); `u` is filtering `.a`.
GroupBy{axis: .a, staticFilter: f, dynamicLabelFilter: u}
Map{parameters: [x, y], dynamicFilter: p} # A 2D Map
Aggregation{function: sum, subject: .x}
```

---

### Static Filter in Aggregated Dynamic GroupBy

```markus
query {
  g(x, y, z),
  groupBy(.a, {
    n()
    sum(.x)
  })
}
```

Layers Chain:

```
# g(x, y, z) = f() ∩ p(x, y) ∩ u(z); `u` is filtering `.a`.
GroupBy{axis: .a, staticFilter: f, dynamicLabelFilter: u}
Map{parameters: [x, y], dynamicFilter: p} # A 2D Map
Aggregation{staticFilter: n, function: sum, subject: .x}
```

---

### Dynamic Filter in Aggregated Dynamic GroupBy

```markus
query {
  g(x, y, z),
  groupBy(.a, {
    n(l, m)
    sum(.x)
  })
}
```

Layers Chain:

```
# g(x, y, z) = f() ∩ p(x, y) ∩ u(z); `u` is filtering `.a`.
GroupBy{axis: .a, staticFilter: f, dynamicLabelFilter: u}
Map{parameters: [x, y], dynamicFilter: p} # A 2D Map
# n(l, m) = s() ∩ q(l, m)
Map{parameters: [l, m], dynamicFilter: q, staticFilter: s}
Aggregation{function: sum, subject: .x}
```

---

### Nested GroupBy

```markus
query {
  groupBy(.a, {
    groupBy(.b)
  })
}
```

Layers Chain:

```
GroupBy{axis: .a}
GroupBy{axis: .b}
```

---

### Nested GroupBy Aggregation

```markus
query {
  groupBy(.a, {
    groupBy(.b, {
      sum(.x)
    }),
    max(.data)
  })
}
```

Layers Chain:

```
GroupBy{axis: .a}
GroupBy{axis: .b, aggregation: Aggregation{function: sum, subject: .data}}
Aggregation{function: sum, subject: .x}
```

---

### Nested GroupBy Filtered Aggregation

```markus
query {
  groupBy(.a, {
    groupBy(.b, {
      sum(.x)
    }),
    f(),
    max(.data)
  })
}
```

Layers Chain:

```
GroupBy{axis: .a}
GroupBy{
  axis: .b,
  aggregation: Aggregation{
    function: sum,
    subject: .data,
    staticFilter: f
  }
}
Aggregation{function: sum, subject: .x}
```

---

### Nested GroupBy Aggregation 2

```markus
query {
  groupBy(.a, {
    groupBy(.b)
    max(.data.x)
  })
}
```

Layers Chain:

```
Error: field does not exists :)
```

---

### Static Filter In GroupBy

```markus
query {
  groupBy(.a, {
    f()
  })
}
```

Layers Chain:

```
GroupBy{axis: .a}
List{staticFilter: f}
```

---

### Static Filter In Aggregated GroupBy

```markus
query {
  groupBy(.a, {
    f(),
    sum(.x)
  })
}
```

Layers Chain:

```
GroupBy{axis: .a}
Aggregation{function: sum, subject: .x, staticFilter: f}
```

---

### Dynamic Filter In GroupBy

```markus
query {
  groupBy(.a, {
    f(x, y)
  })
}
```

Layers Chain:

```
# f(x, y) = g() ∩ h(x) ∩ p(x, y)
GroupBy{axis: .a}
Index{function: h}
List{staticFilter: g, dynamicFilter: p}
```
