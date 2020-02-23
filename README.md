# Markus (BETA)

Markus is specific-purpose programming language that only deals with your database abstractions.

## What?

Markus provides a statically-typed way for developers to express the abstract logic and
functionality of a certain piece of software without going into implementation details.

It provides:

- Type Checking
- Query Optimization
- ACL/Authentication (Permissions)
- Automated Cache Update/Invalidation Proofing
- Online Aggregations
- Code Generation

## Why?

> **TL;DR** We think logics behind every software is complex enough, so let's make implementations
> less complicated.

A software is nothing but the logic that shapes it, and creating a software is implementing those logics with
a combination of technologies that suites the task.

With more complex logic comes higher probability for bugs and mis-function of the program which
might even lead to security wholes.

Sometimes the complexity grows to the level that is beyond
one person comprehension and the programmer can no longer keep track of elements that shape the
program and hence can no longer take decisions such as when to invalidate a certain cache and etc.

## Migrations

Currently in this beta version it's not implemented yet.

## Docs

Checkout the [official documentation](./docs)

## Example

Here is a simple server for a Todo app:

```markus
type User: user {
  name: string;
}

type Task {
  owner: User;
  title: string;
  done: bool;
}

query myTasks() {
  is(Task),
  # %user is the current authenticated user.
  eq(.owner, %user)
}

action newTask($title: string) {
  create Task {
    user: %user,
    title: $title,
    done: false
  };
}

action toggleStatus($task: Task) {
  validate eq($task.owner, %user);

  update $task {
    .done: not(.done)
  };
}

action delete($task: Task) {
  validate eq($task.owner, %user);
  delete $task;
}

action edit($task: Task, $new_title: string) {
  validate eq($task.owner, %user);
  update $task {
    .title: $new_title
  };
}

```
