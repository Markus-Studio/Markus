export interface StructType<T = any> {
  name: string;
  size: number;
  read(view: DataView, offset: number, littleEndian: boolean): T;
  write(view: DataView, offset: number, value: T, littleEndian: boolean): void;
}

export const Int8: StructType<number> = {
  name: "int8",
  size: 1,
  read(view: DataView, offset: number, _: boolean): number {
    return view.getInt8(offset);
  },
  write(view: DataView, offset: number, value: number, _: boolean): void {
    view.setInt8(offset, value);
  }
};

export const Uint8: StructType<number> = {
  name: "uint8",
  size: 1,
  read(view: DataView, offset: number, _: boolean): number {
    return view.getUint8(offset);
  },
  write(view: DataView, offset: number, value: number, _: boolean): void {
    view.setUint8(offset, value);
  }
};

export const Int16: StructType<number> = {
  name: "int16",
  size: 2,
  read(view: DataView, offset: number, littleEndian: boolean): number {
    return view.getInt16(offset, littleEndian);
  },
  write(view: DataView, offset: number, value: number, littleEndian: boolean): void {
    view.setInt16(offset, value, littleEndian);
  }
};

export const UInt16: StructType<number> = {
  name: "uint16",
  size: 2,
  read(view: DataView, offset: number, littleEndian: boolean): number {
    return view.getUint16(offset, littleEndian);
  },
  write(view: DataView, offset: number, value: number, littleEndian: boolean): void {
    view.setUint16(offset, value, littleEndian);
  }
};

export const Int32: StructType<number> = {
  name: "int32",
  size: 4,
  read(view: DataView, offset: number, littleEndian: boolean): number {
    return view.getInt32(offset, littleEndian);
  },
  write(view: DataView, offset: number, value: number, littleEndian: boolean): void {
    view.setInt32(offset, value, littleEndian);
  }
};

export const UInt32: StructType<number> = {
  name: "uint32",
  size: 4,
  read(view: DataView, offset: number, littleEndian: boolean): number {
    return view.getUint32(offset, littleEndian);
  },
  write(view: DataView, offset: number, value: number, littleEndian: boolean): void {
    view.setUint32(offset, value, littleEndian);
  }
};

export const Int64: StructType<bigint | number> = {
  name: "int64",
  size: 8,
  read(view: DataView, offset: number, littleEndian: boolean): bigint | number {
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
  write(view: DataView, offset: number, value: number | bigint, littleEndian: boolean): void {
    const big = typeof value == "bigint" ? value : BigInt(value);
    if ("setBigInt64" in DataView.prototype) {
      view.setBigInt64(offset, big, littleEndian);
    } else {
      // TODO(qti3e)
      throw new Error("Not implemented.");
    }
  }
};

export const UInt64: StructType<bigint | number> = {
  name: "uint64",
  size: 8,
  read(view: DataView, offset: number, littleEndian: boolean): bigint | number {
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
  write(view: DataView, offset: number, value: bigint | number, littleEndian: boolean): void {
    const big = typeof value == "bigint" ? value : BigInt(value);
    if ("setBigInt64" in DataView.prototype) {
      view.setBigInt64(offset, big, littleEndian);
    } else {
      // TODO(qti3e)
      throw new Error("Not implemented.");
    }
  }
};
