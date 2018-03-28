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

AutoCompleteWord& AutoComplete::GetCandidate(AutoCompleteWord &base)
{
	bool matched = false;
	unsigned int i = 0;
	for (; i < candidateCnt && !matched; ++i)
	{
		matched = (strncmp(base.ptr, candidates[i], base.len) == 0);
	}
	if (matched)
	{
		base.ptr = candidates[i - 1];
		base.len = strlen(candidates[i - 1]);
	}
	else
	{
		// Length is set to -1 to indicate no appropriate candidate
		base.len = -1;
	}
	return base;
	// bool matched = false;
	// const char *ans = nullptr;
	// unsigned int i = 0;
	// for (; i < candidateCnt && !matched; ++i)
	// {
	// 	matched = strncmp(base, candidates[i], strlen(base)) == 0;
	// }
	// if (matched)
	// 	ans = candidates[i - 1];
	// else
	// 	ans = base;
	// return ans;
}
