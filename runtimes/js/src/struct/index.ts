import { StructBuilder } from "./builder";

export function struct(name: string = "anonymous") {
  return new StructBuilder(name);
}

const p = struct("X")
  .array(10, _ => _.i8("a"))
  .i64("b")
  .build();

const ab = new ArrayBuffer(p.size);
const view = new DataView(ab);

p.write(view, 0, true, {
  a: "ABCDEFGHIJ",
  b: 7873232389289382039n
});

console.log(ab);

console.log(p.read(view, 0, true));
