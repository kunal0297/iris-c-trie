Class PrefixTrie.Lookup
{

ClassMethod Insert(value As %String)
{
    Set sc = $ZF(-3, "insert", value)
    If sc '= 0 {
        Write "Inserted: ", value, !
    } Else {
        Write "Insert failed for: ", value, !
    }
}

ClassMethod Search(prefix As %String) As %Integer
{
    Set result = $ZF(-3, "search", prefix)
    Write "Search result for prefix '", prefix, "': ", result, !
    Quit result
}
}
#How to Load It in IRIS:
#Do $System.OBJ.Load("PrefixTrie/Lookup.cls", "ck")
