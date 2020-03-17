export type i8 = number;
export type u8 = number;
export type i16 = number;
export type u16 = number;
export type i32 = number;
export type u32 = number;
export type i64 = bigint | number;
export type u64 = bigint | number;

export interface StructType<T> {
  readonly name: string;
  readonly size: number;
  read(view: DataView, offset: number, littleEndian: boolean): T;
  write(view: DataView, offset: number, littleEndian: boolean, value: T): void;
}

export const I8: StructType<i8> = Object.freeze({
  name: "i8",
  size: 1,
  read(view: DataView, offset: number, _: boolean): i8 {
    return view.getInt8(offset);
  },
  write(view: DataView, offset: number, _: boolean, value: i8): void {
    view.setInt8(offset, value);
  }
});

export const U8: StructType<u8> = Object.freeze({
  name: "u8",
  size: 1,
  read(view: DataView, offset: number, _: boolean): u8 {
    return view.getUint8(offset);
  },
  write(view: DataView, offset: number, _: boolean, value: u8): void {
    view.setUint8(offset, value);
  }
});

export const I16: StructType<i16> = Object.freeze({
  name: "i16",
  size: 2,
  read(view: DataView, offset: number, littleEndian: boolean): i16 {
    return view.getInt16(offset, littleEndian);
  },
  write(view: DataView, offset: number, littleEndian: boolean, value: i16): void {
    view.setInt16(offset, value, littleEndian);
  }
});

export const U16: StructType<u16> = Object.freeze({
  name: "u16",
  size: 2,
  read(view: DataView, offset: number, littleEndian: boolean): u16 {
    return view.getUint16(offset, littleEndian);
  },
  write(view: DataView, offset: number, littleEndian: boolean, value: u16): void {
    view.setUint16(offset, value, littleEndian);
  }
});

export const I32: StructType<i32> = Object.freeze({
  name: "i32",
  size: 4,
  read(view: DataView, offset: number, littleEndian: boolean): i32 {
    return view.getInt32(offset, littleEndian);
  },
  write(view: DataView, offset: number, littleEndian: boolean, value: i32): void {
    view.setInt32(offset, value, littleEndian);
  }
});

export const U32: StructType<u32> = Object.freeze({
  name: "u32",
  size: 4,
  read(view: DataView, offset: number, littleEndian: boolean): u32 {
    return view.getUint32(offset, littleEndian);
  },
  write(view: DataView, offset: number, littleEndian: boolean, value: u32): void {
    view.setUint32(offset, value, littleEndian);
  }
});

export const I64: StructType<i64> = Object.freeze({
  name: "i64",
  size: 8,
  read(view: DataView, offset: number, littleEndian: boolean): i64 {
    let n: bigint;
    if ("getBigInt64" in DataView.prototype) {
      n = view.getBigInt64(offset, littleEndian);
    } else {
      let value = 0n;
      let isNegative = (view.getUint8(offset + (littleEndian ? 7 : 0)) & 0x80) > 0;
      let carrying = true;
      for (let i = 0; i < 8; i++) {
        let byte = view.getUint8(offset + (littleEndian ? i : 7 - i));
        if (isNegative) {
          if (carrying) {
            if (byte != 0x00) {
              byte = ~(byte - 1) & 0xff;
              carrying = false;
            }
          } else {
            byte = ~byte & 0xff;
          }
        }
        value += BigInt(byte) * 256n ** BigInt(i);
      }
      if (isNegative) {
        value = -value;
      }
      n = value;
    }
    return n <= Number.MAX_SAFE_INTEGER ? Number(n) : n;
  },
  write(view: DataView, offset: number, littleEndian: boolean, value: i64): void {
    const big = typeof value == "bigint" ? value : BigInt(value);
    if ("setBigInt64" in DataView.prototype) {
      view.setBigInt64(offset, big, littleEndian);
    } else {
      // TODO(qti3e)
      throw new Error("Not implemented.");
    }
  }
});

export const U64: StructType<u64> = Object.freeze({
  name: "u64",
  size: 8,
  read(view: DataView, offset: number, littleEndian: boolean): u64 {
    let n: bigint;
    if ("getBigUint64" in DataView.prototype) {
      n = view.getBigUint64(offset, littleEndian);
    } else {
      const lsb = BigInt(view.getUint32(offset + (littleEndian ? 0 : 4), littleEndian));
      const gsb = BigInt(view.getUint32(offset + (littleEndian ? 4 : 0), littleEndian));
      n = lsb + 4294967296n * gsb;
    }
    return n <= Number.MAX_SAFE_INTEGER ? Number(n) : n;
  },
  write(view: DataView, offset: number, littleEndian: boolean, value: u64): void {
    const big = typeof value == "bigint" ? value : BigInt(value);
    if ("setBigInt64" in DataView.prototype) {
      view.setBigInt64(offset, big, littleEndian);
    } else {
      // TODO(qti3e)
      throw new Error("Not implemented.");
    }
  }
});
