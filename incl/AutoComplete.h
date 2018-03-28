#ifndef _AUTO_COMPLETE_H_
#define _AUTO_COMPLETE_H_

struct AutoCompleteWord
{
	const char *ptr = nullptr;
	int len = 0;
};

class AutoComplete
{
public:
	static constexpr unsigned int MAX_NUMBER_OF_CANDIDATES = 64;
	static constexpr unsigned int MAX_CANDIDATE_LEN = 64;

	AutoComplete();
	AutoComplete(char **candidateList, unsigned int numOfCand);
	void AddToCandidates(const char *candidate);
	AutoCompleteWord& GetCandidate(AutoCompleteWord &base);
private:
	char candidates[MAX_NUMBER_OF_CANDIDATES][MAX_CANDIDATE_LEN] = { "auto", "complete", "list" };
	unsigned int candidateCnt = 3;
};

#endif