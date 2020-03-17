import { Struct, StructMember } from "./struct";
import { StructType } from "./types";
import * as types from "./types";

export class StructBuilder<T extends object> {
  private members: StructMember[] = [];
  private maxElementSize = 0;
  private count = [1];

  constructor(private readonly name: string) {}

  private getNextOffset(align: number): number {
    const len = this.members.length;
    if (len === 0) return 0;
    const member = this.members[len - 1];
    const size = member.type.size * member.count;
    const offset = member.offset + size;
    if (align > 1) {
      const pow = fastSqrtTwo(align);
      return nextNumberDividableByPowOfTwo(offset, pow);
    }
    return offset;
  }

  private getCount() {
    return this.count[this.count.length - 1];
  }

  private atomic(name: string, type: StructType<any>): this {
    const offset = this.getNextOffset(type.size);
    if (type.size > this.maxElementSize) {
      this.maxElementSize = type.size;
    }
    this.members.push({
      name,
      offset,
      type,
      count: this.getCount()
    });
    return this;
  }

  array<O extends StructBuilder<T>>(count: number, cb: (o: this) => O): O {
    if (count <= 1) throw new Error("Illegal array size.");
    this.count.push(count);
    try {
      return cb(this);
    } catch (e) {
      throw e;
    } finally {
      this.count.pop();
    }
  }

  build(): Struct<T> {
    const size = this.getNextOffset(this.maxElementSize);
    return new Struct(this.name, this.members, size, this.maxElementSize);
  }

  struct(name: string, struct: Struct<any>): this {
    const maxElementSize = struct.maxElementSize;
    const offset = this.getNextOffset(maxElementSize);
    if (maxElementSize > this.maxElementSize) {
      this.maxElementSize = maxElementSize;
    }
    this.members.push({
      name,
      offset,
      type: struct,
      count: this.getCount()
    });

    return this;
  }

  i8(name: string): this {
    return this.atomic(name, types.I8);
  }

  u8(name: string): this {
    return this.atomic(name, types.U8);
  }

  i16(name: string): this {
    return this.atomic(name, types.I16);
  }

  u16(name: string): this {
    return this.atomic(name, types.U16);
  }

  i32(name: string): this {
    return this.atomic(name, types.I32);
  }

  u32(name: string): this {
    return this.atomic(name, types.U32);
  }

  i64(name: string): this {
    return this.atomic(name, types.I64);
  }

  u64(name: string): this {
    return this.atomic(name, types.U64);
  }
}

function nextNumberDividableByPowOfTwo(number: number, pow: number): number {
  const n = (number >> pow) << pow;
  if (n === number) return n;
  return n + (1 << pow);
}

function fastSqrtTwo(n: number): number {
  let i = 0;
  for (; n; n >>= 1) {
    i++;
  }
  return i - 1;
}
