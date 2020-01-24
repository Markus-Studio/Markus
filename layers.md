# Markus Layers IR

---
**Static List**
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
**Dynamic List**
```markus
query {
  f(),
  g(x, y)
}
```
Layers Chain
```
# g(x, y) = h(x) ∩ p(x, y); where `h` is indexable.
Index{function: h}
List{staticFilter: f, dynamicFilter: p}
```

---
**Simple Static GroupBy**
```markus
query {
  f(),
  groupBy(.a)
}
```
Layers Chain:
```
GroupBy{axises: [.a], staticFilter: f}
List{}
```

---
**Simple Dynamic GroupBy**
```markus
query {
  f(),
  g(x, y),
  groupBy(.a)
}
```
Layers Chain:
```
# g(x, y) = h(x) ∩ p(x, y) ∩ u(y); where `h` is indexable.
# and `u` is filtering `.a`
GroupBy{axises: [.a], staticFilter: f, dynamicLabelFilter: u}
Index{function: h} # If h is not empty.
List{dynamicFilter: p}
```

---
**Aggregated Static GroupBy**
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
GroupBy{axises: [.a], staticFilter: f}
Aggregation{subject: .x}
```

---
**Aggregated Dynamic GroupBy**
```markus
query {
  f(),
  g(x, y, z),
  groupBy(.a, {
    sum(.x)
  })
}
```
Layers Chain:
```
# g(x, y, z) = p(x, y) ∩ u(z); `u` is filtering `.a`.
GroupBy{axises: [.a], staticFilter: f, dynamicLabelFilter: u}
Map{parameters: [x, y], dynamicFilter: p} # A 2D Map
Aggregation{subject: .x}
```