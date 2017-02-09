
@dic={}

def cache_initialize()

end

def cache_has_key(key: String)
    return @dic.has_key? key
end

def cache_set(key: String,value: String)
    @dic[key] = value
end

def cache_get(key: String)
    @dic[key]
end

cache_initialize()

puts cache_has_key(key: "key")
cache_set(key: "key",value: "hola")
puts cache_has_key(key: "key")
puts cache_get(key: "key")
