import { StructType } from "./types";

export interface StructMember {
  name: string;
  offset: number;
  type: StructType;
  count: number;
}

export class Struct<T extends object> implements StructType {
  constructor(
    readonly name: string,
    readonly members: ReadonlyArray<StructMember>,
    readonly size: number,
    readonly maxElementSize: number
  ) {}

  read(view: DataView, offset: number, littleEndian: boolean): T {
    throw new Error("");
  }

  write(view: DataView, offset: number, littleEndian: boolean, value: T): void {
    throw new Error("");
  }
}
