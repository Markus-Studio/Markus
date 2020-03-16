import { StructBuilder } from "./builder";

export function struct() {
  return new StructBuilder();
}

// const p = struct()
//   .int('x')
//   .char('u')
//   .build();

// p.size();
// p.offsetOf('x');

// p.write[|BE|LE](buf, {
//   x: 4,
//   u: 9
// });

// p.read(buf).x;
