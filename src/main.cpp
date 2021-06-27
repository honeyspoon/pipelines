#include <stdio.h>
#include <unistd.h>
#include <string>

pid_t pid = getpid();
void log(std::string && s)
{
	fprintf(stderr, "[%d] %s\n", pid, s.c_str());
}

int main()
{
	log("start");

	FILE *const in = fdopen(dup(fileno(stdin)), "rb");
	FILE *const out = fdopen(dup(fileno(stdout)), "wb");

	constexpr size_t BUFFER_LENGTH = 1024;
	constexpr int NB_OBJECTS = 1;

	char buffer[BUFFER_LENGTH * NB_OBJECTS];

	bool eof = false;

	while(!eof)
	{
		size_t read_bytes = fread((void*) buffer, BUFFER_LENGTH, NB_OBJECTS, in);
		if (read_bytes == 0) {
			log("eof");
			eof = true;
		}
		if (!eof && read_bytes != NB_OBJECTS){
			log("incomplete read");
		} 
		size_t written_bytes = fwrite((void*) buffer, BUFFER_LENGTH, NB_OBJECTS, out);
		if (written_bytes == 0) {
			log("eof write wtf");
		}
		if (written_bytes != NB_OBJECTS){
			log("incomplete write");
		} 
	}

	fclose(in);
	fclose(out);

	return 0;
}
