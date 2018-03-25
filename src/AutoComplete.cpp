#include <string.h>
#include <AutoComplete.h>

AutoComplete::AutoComplete()
{

}

AutoComplete::AutoComplete(char **candidateList, unsigned int numOfCand)
{
	candidateCnt = numOfCand;
	if (candidateCnt > MAX_NUMBER_OF_CANDIDATES)
		candidateCnt = MAX_NUMBER_OF_CANDIDATES;
	for (unsigned int i = 0; i < candidateCnt; ++i)
	{
		strcpy(candidates[i], candidateList[i]);
	}
}

void AutoComplete::AddToCandidates(const char *candidate)
{
	if (candidateCnt < MAX_NUMBER_OF_CANDIDATES)
		strcpy(candidates[candidateCnt], candidate);
}

const char * AutoComplete::GetCandidate(const char *base)
{
	bool matched = false;
	const char *ans = nullptr;
	unsigned int i = 0;
	for (; i < candidateCnt && !matched; ++i)
	{
		matched = strncmp(base, candidates[i], strlen(base)) == 0;
	}
	if (matched)
		ans = candidates[i - 1];
	else
		ans = base;
	return ans;
}
