import { Struct } from "./struct";

export class StructBuilder {
  int(name: string): StructBuilder {
    return this;
  }

  build(): Struct {
    return new Struct([]);
  }
}
