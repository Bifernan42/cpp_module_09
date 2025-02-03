#!/bin/bash

classes=()

for class in includes/[A-Z]*.hpp; do
    echo "#include \"${class#includes/}\"" >> srcs/main.cpp
    if ! [ -s "$class" ]; then
        className="${class#includes/}"
        className="${className%.hpp}"
        classes+=("$className")
    fi
done

for class in "${classes[@]}"; do
  	
    class_upper=$(echo "$class" | tr 'a-z' 'A-Z')
  
    echo "#ifndef ${class_upper}_HPP
# define ${class_upper}_HPP
# include \"../../lib/includes/cpplib.hpp\"
# include <iostream>
# include <deque>
# include <vector>
# include <map>
# include <list>

class $class
{
    public:
        $class();
        ~$class();
        $class &operator=(const $class &);
        $class(const $class &);
};

#endif" > "includes/${class}.hpp" 

    echo "#include \"${class}.hpp\"

$class::$class()
{

}

$class::~$class()
{

}

$class &$class::operator=(const $class &other)
{
	(void)other;
	return *this;
}

$class::$class(const $class &other)
{
	(void)other;
}

"> "srcs/${class}.cpp"

done

