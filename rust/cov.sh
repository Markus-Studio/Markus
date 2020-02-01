#!/bin/bash
find . \( -name "*.gcda" \) -delete

export CARGO_INCREMENTAL=0
export RUSTFLAGS="-Zprofile -Ccodegen-units=1 -Cinline-threshold=0 -Clink-dead-code -Coverflow-checks=off -Zno-landing-pads"
cargo build --verbose $CARGO_OPTIONS
cargo test --verbose $CARGO_OPTIONS
zip -0 ccov.zip `find . \( -name "markus*.gc*" \) -print`;
grcov ccov.zip -s . --llvm --branch --ignore-not-existing --ignore "/*" -o cov-report -t html
rm ccov.zip
unset CARGO_INCREMENTAL
unset RUSTFLAGS