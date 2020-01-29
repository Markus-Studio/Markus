// From microsoft/vscode-languageserver-node
extern crate markus;
use markus::parser::source::*;

#[cfg(test)]
fn get_source(data: &str) -> Source {
    Source::new(String::from("foo://bar"), data)
}

// TODO(qti3e) Test effected regions.

#[test]
fn inserts() {
    {
        let mut source = get_source("012345678901234567890123456789");
        assert_eq!(
            source.apply_edits(&mut vec![TextEdit::insert(
                Position::new(0, 0),
                String::from("Hello"),
            )]),
            Range::new(Position::new(0, 0), Position::new(0, 5))
        );
        assert_eq!(
            "Hello012345678901234567890123456789",
            source.get_content_utf8()
        );
    }

    {
        let mut source = get_source("012345678901234567890123456789");
        assert_eq!(
            source.apply_edits(&mut vec![TextEdit::insert(
                Position::new(0, 1),
                String::from("Hello"),
            )]),
            Range::new(Position::new(0, 1), Position::new(0, 6))
        );
        assert_eq!(
            "0Hello12345678901234567890123456789",
            source.get_content_utf8()
        );
    }

    {
        let mut source = get_source("012345678901234567890123456789");
        source.apply_edits(&mut vec![
            TextEdit::insert(Position::new(0, 1), String::from("Hello")),
            TextEdit::insert(Position::new(0, 1), String::from("World")),
        ]);
        assert_eq!(
            "0HelloWorld12345678901234567890123456789",
            source.get_content_utf8()
        );
    }

    {
        let mut source = get_source("012345678901234567890123456789");
        source.apply_edits(&mut vec![
            TextEdit::insert(Position::new(0, 2), String::from("One")),
            TextEdit::insert(Position::new(0, 1), String::from("Hello")),
            TextEdit::insert(Position::new(0, 1), String::from("World")),
            TextEdit::insert(Position::new(0, 2), String::from("Two")),
            TextEdit::insert(Position::new(0, 2), String::from("Three")),
        ]);
        assert_eq!(
            "0HelloWorld1OneTwoThree2345678901234567890123456789",
            source.get_content_utf8()
        );
    }
}

#[test]
fn replace() {
    {
        let mut source = get_source("012345678901234567890123456789");
        source.apply_edits(&mut vec![TextEdit::replace(
            Position::new(0, 3),
            Position::new(0, 6),
            String::from("Hello"),
        )]);
        assert_eq!(
            "012Hello678901234567890123456789",
            source.get_content_utf8()
        );
    }

    {
        let mut source = get_source("012345678901234567890123456789");
        source.apply_edits(&mut vec![TextEdit::replace(
            Position::new(0, 3),
            Position::new(0, 6),
            String::from("Hello"),
        )]);
        assert_eq!(
            "012Hello678901234567890123456789",
            source.get_content_utf8()
        );
    }

    {
        let mut source = get_source("012345678901234567890123456789");
        source.apply_edits(&mut vec![
            TextEdit::replace(
                Position::new(0, 3),
                Position::new(0, 6),
                String::from("Hello"),
            ),
            TextEdit::replace(
                Position::new(0, 6),
                Position::new(0, 9),
                String::from("World"),
            ),
        ]);
        assert_eq!(
            "012HelloWorld901234567890123456789",
            source.get_content_utf8()
        );
    }

    {
        let mut source = get_source("012345678901234567890123456789");
        source.apply_edits(&mut vec![
            TextEdit::replace(
                Position::new(0, 3),
                Position::new(0, 6),
                String::from("Hello"),
            ),
            TextEdit::insert(Position::new(0, 6), String::from("World")),
        ]);
        assert_eq!(
            "012HelloWorld678901234567890123456789",
            source.get_content_utf8()
        );
    }

    {
        let mut source = get_source("012345678901234567890123456789");
        source.apply_edits(&mut vec![
            TextEdit::insert(Position::new(0, 6), String::from("World")),
            TextEdit::replace(
                Position::new(0, 3),
                Position::new(0, 6),
                String::from("Hello"),
            ),
        ]);
        assert_eq!(
            "012HelloWorld678901234567890123456789",
            source.get_content_utf8()
        );
    }

    {
        let mut source = get_source("012345678901234567890123456789");
        source.apply_edits(&mut vec![
            TextEdit::insert(Position::new(0, 3), String::from("World")),
            TextEdit::replace(
                Position::new(0, 3),
                Position::new(0, 6),
                String::from("Hello"),
            ),
        ]);
        assert_eq!(
            "012WorldHello678901234567890123456789",
            source.get_content_utf8()
        );
    }
}

#[test]
fn multiline() {
    let mut source = get_source("0\n1\n2\n3\n4");
    source.apply_edits(&mut vec![
        TextEdit::replace(
            Position::new(2, 0),
            Position::new(3, 0),
            String::from("Hello"),
        ),
        TextEdit::insert(Position::new(1, 1), String::from("World")),
    ]);
    assert_eq!("0\n1World\nHello3\n4", source.get_content_utf8());
}