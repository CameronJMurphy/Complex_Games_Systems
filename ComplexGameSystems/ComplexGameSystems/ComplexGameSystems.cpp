#include <iostream>
#include <thread>#include <vector>#include <mutex>#define GLM_ENABLE_EXPERIMENTAL#include <glm/glm.hpp>

void Print(int i)
{
	static std::mutex myMutex;
	std::lock_guard<std::mutex> guard(myMutex);


	std::cout << "Hello Thread" << i << "\n";
	std::cout << "I'm here...\n";
	std::cout << "...not there.\n";
}


int main()
{
	std::vector<std::thread> threads;
	std::mutex myMutex;
	glm::vec4 myVectors[50000];
	int chunkLength = 50000 / 10;
	for (int i = 0; i < 10; i++) {
		threads.push_back(std::thread(
			// defining a lambda that can access main scope with &
			[&](int low, int high) {
				for (int j = low; j < high; j++)
					myVectors[j] = normalize(myVectors[j]);
			}, i * chunkLength, (i + 1) * chunkLength
				));
	}
	for (auto& thread : threads)
	{
		thread.join();
	}	return 0;
}

