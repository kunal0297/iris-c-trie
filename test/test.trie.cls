Class test.trie
{

ClassMethod Run()
{
    Write !, "== Inserting Words ==", !
    Set sc = ##class(PrefixTrie.Lookup).Insert("kunal") If $$$ISERR(sc) Quit
    Set sc = ##class(PrefixTrie.Lookup).Insert("kumar") If $$$ISERR(sc) Quit
    Set sc = ##class(PrefixTrie.Lookup).Insert("karma") If $$$ISERR(sc) Quit
    Set sc = ##class(PrefixTrie.Lookup).Insert("karan") If $$$ISERR(sc) Quit

    Write !, "== Running Searches ==", !
    Do ..SearchAndShow("ku")
    Do ..SearchAndShow("ka")
    Do ..SearchAndShow("k")
    Do ..SearchAndShow("x")
    Do ..SearchAndShow("")
}

ClassMethod SearchAndShow(prefix As %String)
{
    Write !, "Searching for prefix: '", prefix, "'", !
    Set result = $ZF(-3, "search", prefix)
    If result '= "" {
        Write "First match: ", result, !
    } Else {
        Write "No match found.", !
    }
}

}
