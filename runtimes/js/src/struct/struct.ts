import { StructType } from "./types";

export interface StructMember {
  name: string;
  offset: number;
  type: StructType<any>;
  count: number;
}

export class Struct<T extends object> implements StructType<T> {
  readonly map: ReadonlyMap<string, StructMember>;

  constructor(
    readonly name: string,
    readonly members: ReadonlyArray<StructMember>,
    readonly size: number,
    readonly maxElementSize: number
  ) {
    const map = new Map<string, StructMember>();
    for (const member of members) {
      map.set(member.name, member);
    }
    this.map = map;
  }

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
        } else if (typeof data.length === "number") {
          const m = Math.min(count, data.length);
          for (let i = 0; i < m; ++i) {
            type.write(view, offset, littleEndian, data[i]);
            offset += type.size;
          }
        } else {
          throw new Error(`Expected an array for field '${name}'`);
        }
      } else {
        type.write(view, offset, littleEndian, data);
      }
    }
  }

  get<K extends keyof T & string>(
    view: DataView,
    baseOffset: number,
    littleEndian: boolean,
    key: K
  ): T[K] {
    let { count, offset, type } = this.map.get(key)!;
    offset += baseOffset;
    if (count > 1) {
      const data: any = new Array(count);

      for (let i = 0; i < count; ++i) {
        data[i] = type.read(view, offset, littleEndian);
        offset += type.size;
      }

      return data;
    } else {
      return type.read(view, offset, littleEndian);
    }
  }
}
