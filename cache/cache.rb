@@dic={}

def __metacall_initialize__()

	puts 'ruby: initialize'

	@@dic={}

end

def cache_has_key(key: String)

	puts 'ruby: has key'

	return @@dic.has_key? key

end

def cache_set(key: String, value: String)

	puts 'ruby: set value'

	@@dic[key] = value

end

def cache_get(key: String)

	puts 'ruby: get value'

	@@dic[key]

end

def __metacall_finalize__()

	puts 'ruby: finalize'

end
