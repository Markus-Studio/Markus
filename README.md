# Markus Cpp

This repository contains the source code of the reference implementation of the
Markus language in C++.

Markus is a specific purpose programming language that generates highly-optimized
database servers for a predefined set of actions and queries, servers generated by
Markus are real-time, as in term of receiving query result updates, a client can
connect to the database over a WS connection, and once they're authorized, they
can subscribe to any query (AKA A Data Source) they want and get the real-time
updates from the database as they happen.

This implementation is written on the mindset that it's not going to be used as a
compilation server/service and it exits once it compiles a single document, so not
much of an effort has gone through not-having memory leaks.

I hate C++, the only reason it's written in C++ over any other language is the
fact that I personally wanted to improve my own professional skills in this
language.

## JIT Queries/Actions

It's not going to happen anytime soon, but if we decide to support this feature
we will definitely be using LLVM JIT compiler.

## Migrations

To be planned.

## Backend

Currently only a C backend is planned ahead, but one day we will be producing
binaries using LLVM, but for now it's a total waste of budget.

## Storage Engines

If we wanted to use one storage engine for every database we would be using MySQL,
or any other database, one of the points of implementing Markus is to generate a
unique storage engine for each Markus Document so that the system performs better. 
