Class test.trie
{

ClassMethod Run()
{
    Do ##class(PrefixTrie.Lookup).Insert("kunal")
    Do ##class(PrefixTrie.Lookup).Insert("kumar")
    Do ##class(PrefixTrie.Lookup).Insert("karma")
    Do ##class(PrefixTrie.Lookup).Insert("karan")

    Do ##class(PrefixTrie.Lookup).Search("ku")
    Do ##class(PrefixTrie.Lookup).Search("ka")
    Do ##class(PrefixTrie.Lookup).Search("x") // No match
}
}
