Class PrefixTrie.Lookup
{
    ClassMethod Initialize() As %Status
    {
        If '$Data(^PrefixTrieLibLoaded) {
            Set sc = $ZF(-3, "/usr/lib/libfastlookup.so")
            If sc '= 0 {
                Write "Shared library loaded successfully", !
                Set ^PrefixTrieLibLoaded = 1
                Quit $$$OK
            } Else {
                Write " ERROR: Failed to load shared library", !
                Quit $$$ERROR
            }
        }
        Quit $$$OK
    }

    ClassMethod Insert(value As %String) As %Status
    {
        Do ..Initialize()
        Set sc = $ZF(-3, "insert", value)
        If sc '= 0 {
            Write "Inserted: ", value, !
            Quit $$$OK
        } Else {
            Write "Insert failed for: ", value, !
            Quit $$$ERROR
        }
    }

    ClassMethod Search(prefix As %String) As %Integer
    {
        Do ..Initialize()

        Set result = $ZF(-3, "search", prefix)
        
        If result '= 0 {
            Write "Matches found for prefix '", prefix, "': ", result, !
        } Else {
            Write "No matches found for prefix '", prefix, "'", !
        }
        
        Quit result
    }
}
