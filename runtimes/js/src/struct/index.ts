import { StructBuilder } from "./builder";

export function struct<P extends Object>(name: string = "anonymous") {
  return new StructBuilder<P>(name);
}

interface P {
  a: number[];
  b: bigint | number;
}

const p = struct<P>("X")
  .array(10, _ => _.i8("a"))
  .i64("b")
  .build();

const ab = new ArrayBuffer(p.size);
const view = new DataView(ab);

p.write(view, 0, true, {
  a: [10, 11, 12, 13],
  b: 7873232389289382039n
});

console.log(ab);

const o = p.read(view, 0, true);

console.log(o.a);
