Class PrefixTrie.Lookup
{

ClassMethod Initialize() As %Status
{
    If '$Data(^PrefixTrieLibLoaded) {
        // Load the shared library
        Set sc = $ZF(-3, "/usr/lib/libfastlookup.so")
        If sc = 0 {
            Write "Shared library loaded successfully", !
            Set ^PrefixTrieLibLoaded = 1
            Quit $$$OK
        } Else {
            Write "ERROR: Failed to load shared library", !
            Quit $$$ERROR($$$GeneralError, "Failed to load /usr/lib/libfastlookup.so")
        }
    }
    Quit $$$OK
}

ClassMethod Insert(value As %String) As %Status
{
    Set sc = ..Initialize()
    If $$$ISERR(sc) {
        Quit sc
    }

    New result
    Set result = $ZF(-3, "insert", value)

    If result = 0 {
        Write "Inserted: ", value, !
        Quit $$$OK
    } Else {
        Write "Insert failed for: ", value, " (code=", result, ")", !
        Quit $$$ERROR($$$GeneralError, "Insert failed")
    }
}

ClassMethod Search(prefix As %String) As %Status
{
    Set sc = ..Initialize()
    If $$$ISERR(sc) {
        Write "Initialization failed. Cannot perform search.", !
        Quit $$$ERROR($$$GeneralError, "Library initialization failed")
    }

    New result
    Set result = $ZF(-3, "search", prefix)

    If result '= "" {
        Write "First match for prefix '", prefix, "': ", result, !
    } Else {
        Write "No matches found for prefix '", prefix, "'", !
    }

    Quit $$$OK
}

}
