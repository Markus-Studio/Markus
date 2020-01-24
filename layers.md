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
**Static Aggregation**
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
**Dynamic Aggregation**
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
  g(x, y),
  groupBy(.a)
}
```
Layers Chain:
```
# g(x, y) = f() ∩ h(x) ∩ p(x, y) ∩ u(y); where `h` is indexable.
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
Aggregation{function: sum, subject: .x}
```

---
**Aggregated Dynamic GroupBy**
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
GroupBy{axises: [.a], staticFilter: f, dynamicLabelFilter: u}
Map{parameters: [x, y], dynamicFilter: p} # A 2D Map
Aggregation{function: sum, subject: .x}
```