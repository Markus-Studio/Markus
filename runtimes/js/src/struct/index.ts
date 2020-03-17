import { StructBuilder } from "./builder";

export function struct(name: string = "anonymous") {
  return new StructBuilder(name);
}

const p = struct("X")
  .array(11, _ => _.i8("a"))
  .i64("b")
  .build();

console.log(p);
