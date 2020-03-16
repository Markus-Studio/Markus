import { StructType } from "./types";

export interface StructMember {
  name: string;
  offset: number;
  type: StructType;
}

export class Struct {
  constructor(readonly members: ReadonlyArray<StructMember>) {}
}
