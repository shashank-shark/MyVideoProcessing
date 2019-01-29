/* include the necessary libraries */
#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

/* function to execute the given command */
std::string exec (const char* cmd)
{
	std:array<char,128> buffer;
	std:string result;

	auto pipe = popen (cmd,"r");

	/* check if the pipe access is granted and fully functional */
	if (!pipe) throw std::runtime_error ("popen() failed.");

	while (!feof(pipe))
	{
		if (fgets(buffer.data(),128,pipe) != nullptr)
		{
			result += buffer.data();
		}
	}

	auto rc = pclose(pipe);
    
    if (rc == EXIT_SUCCESS)
    {
        std::cout << "SUCCESS\n";
    }
    else
    {
        std::cout << "FAILED\n";
    }
    
    return result;
}

using namespace std;

int main (int argc, char *argv[])
{
	std::string res;
	res = exec("");
	std::cout << "OUTPUT" << res << std::endl;

	return 0;
}