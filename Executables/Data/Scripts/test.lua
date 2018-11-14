print("test.lua initialized")

aglobal = "KUK!"

local test = {
	subtable = {
		value0 = "Horse",
		value1 = "Dog",
		value2 = true
	}
}

function printTable ( t )
	local print_r_cache={}
    local function sub_print_r(t,indent)
        if (print_r_cache[tostring(t)]) then
            print(indent.."*"..tostring(t))
        else
            print_r_cache[tostring(t)]=true
            if (type(t)=="table") then
                for pos,val in pairs(t) do
                    if (type(val)=="table") then
                        print(indent.."["..pos.."] => "..tostring(t).." {")
                        sub_print_r(val,indent..string.rep(" ",string.len(pos)+8))
                        print(indent..string.rep(" ",string.len(pos)+6).."}")
                    elseif (type(val)=="string") then
                        print(indent.."["..pos..'] => "'..val..'"')
                    else
                        print(indent.."["..pos.."] => "..tostring(val))
                    end
                end
            else
                print(indent..tostring(t))
            end
        end
    end
    if (type(t)=="table") then
        print(tostring(t).." {")
        sub_print_r(t,"  ")
        print("}")
    else
        sub_print_r(t,"  ")
    end
    print()
end

function test2()
    return "Hello world", -42, 42, 42.42
end

function test3()
    print("Hello world 3!")
end

function test4()
    print("storedValue: "..myTable.storedValue)
    return myTable.storedValue
end

function testing(a,b,c)
	return c, a, b
end

return test