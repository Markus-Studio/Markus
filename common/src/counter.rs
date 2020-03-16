use std::collections::HashMap;

/// A counter that can be used to counter number of things based on a key.
pub trait Counter<K> {
    /// Increments the counter by one.
    fn incr(&mut self, key: K);
    /// Decrements the counter by one.
    fn decr(&mut self, key: K);
    /// Returns the count.
    fn get_count(&self, key: &K) -> i32;
}

impl<K> Counter<K> for HashMap<K, i32>
where
    K: std::cmp::Eq + std::hash::Hash,
{
    fn incr(&mut self, key: K) {
        let current = *self.get(&key).unwrap_or(&0);
        self.insert(key, current + 1);
    }

    fn decr(&mut self, key: K) {
        let current = *self.get(&key).unwrap_or(&0);
        self.insert(key, current - 1);
    }

    fn get_count(&self, key: &K) -> i32 {
        *self.get(key).unwrap_or(&0)
    }
}
