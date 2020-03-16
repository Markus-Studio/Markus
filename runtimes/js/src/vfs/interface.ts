type Int32 = number;

type BlockNumber = Int32;

export interface ReadonlyVFS {
  read(
    block_number: BlockNumber,
    read_offset: Int32,
    buffer: Uint8Array,
    count?: Int32,
    write_offset?: Int32
  ): Promise<void>;

  readSync(
    block_number: BlockNumber,
    read_offset: Int32,
    buffer: Uint8Array,
    count?: Int32,
    write_offset?: Int32
  ): void;

  readInt32(): Promise<number>;
  readInt32Sync(): number;
  readInt32BE(): Promise<number>;
  readInt32BESync(): number;
  readInt32LE(): Promise<number>;
  readInt32LESync(): number;

  readUInt32(): Promise<number>;
  readUInt32Sync(): number;
  readUInt32BE(): Promise<number>;
  readUInt32BESync(): number;
  readUInt32LE(): Promise<number>;
  readUInt32LESync(): number;
}

export interface WritableVFS extends ReadonlyVFS {
  alloc(count?: number): Promise<BlockNumber[]>;
  allocSync(count?: number): BlockNumber[];

  free(blocks: BlockNumber[]): Promise<void>;
  freeSync(blocks: BlockNumber[]): void;

  write(
    block_number: BlockNumber,
    write_offset: Int32,
    buffer: Uint8Array,
    count?: Int32,
    read_offset?: Int32
  ): Promise<void>;

  writeSyn(
    block_number: BlockNumber,
    write_offset: Int32,
    buffer: Uint8Array,
    count?: Int32,
    read_offset?: Int32
  ): void;
}

export type VFS = WritableVFS;
