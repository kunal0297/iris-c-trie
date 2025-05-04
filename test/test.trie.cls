Class test.trie
{
    ClassMethod Run()
    {
        // Insert words into the PrefixTrie
        Do ##class(PrefixTrie.Lookup).Insert("kunal")
        Do ##class(PrefixTrie.Lookup).Insert("kumar")
        Do ##class(PrefixTrie.Lookup).Insert("karma")
        Do ##class(PrefixTrie.Lookup).Insert("karan")

        // Test searching for different prefixes
        Write !, "Search for 'ku':"
        Do ##class(PrefixTrie.Lookup).Search("ku")  // Should return matches for "kunal", "kumar"

        Write !, "Search for 'ka':"
        Do ##class(PrefixTrie.Lookup).Search("ka")  // Should return matches for "karma", "karan"

        Write !, "Search for 'k':"
        Do ##class(PrefixTrie.Lookup).Search("k")   // Should return all matches: "kunal", "kumar", "karma", "karan"

        Write !, "Search for 'x':"
        Do ##class(PrefixTrie.Lookup).Search("x")   // No match, should handle gracefully

        Write !, "Search for an empty prefix '':"
        Do ##class(PrefixTrie.Lookup).Search("")    // Edge case for empty prefix, handle as needed
    }
}
