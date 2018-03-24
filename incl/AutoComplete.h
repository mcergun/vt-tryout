#ifndef _AUTO_COMPLETE_H_
#define _AUTO_COMPLETE_H_

class AutoComplete
{
public:
	AutoComplete();
	AutoComplete(char **candidateList, unsigned int numOfCand);
	void AddToCandidates(const char *candidate);
	const char * GetCandidate(const char *base);
private:
	static constexpr unsigned int MAX_NUMBER_OF_CANDIDATES = 64;
	static constexpr unsigned int MAX_CANDIDATE_LEN = 64;
	char candidates[MAX_NUMBER_OF_CANDIDATES][MAX_CANDIDATE_LEN] = { 0 };
	unsigned int candidateCnt = 0;
};

#endif