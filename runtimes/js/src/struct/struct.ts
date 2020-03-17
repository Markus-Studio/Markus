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

  read(view: DataView, base: number, littleEndian: boolean): T {
    const obj: any = {};

    for (let { name, offset, type, count } of this.members) {
      offset += base;
      if (count > 1) {
        const data = new Array(count);

        for (let i = 0; i < count; ++i) {
          data[i] = type.read(view, offset, littleEndian);
          offset += type.size;
        }

        obj[name] = data;
      } else {
        obj[name] = type.read(view, offset, littleEndian);
      }
    }

    return obj as T;
  }

  write(view: DataView, base: number, littleEndian: boolean, value: T): void {
    for (let { name, offset, type, count } of this.members) {
      const data = (value as any)[name];

      offset += base;
      if (count > 1) {
        if (typeof data === "string") {
          const m = Math.min(count, data.length);
          for (let i = 0; i < m; ++i) {
            type.write(view, offset, littleEndian, data.charCodeAt(i));
            offset += type.size;
          }
          continue;
        }

        if (!(data instanceof Array)) {
          throw new Error(`Expected an array for field '${name}'`);
        }

        for (let i = 0; i < count; ++i) {
          type.write(view, offset, littleEndian, data[i]);
          offset += type.size;
        }
      } else {
        type.write(view, offset, littleEndian, data);
      }
    }
  }
}
