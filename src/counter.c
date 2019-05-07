/**
 * @brief Red Pitaya counter module
 *
 * @author Roger John, roger.john@uni-leipzig.de
 * @author Robert Staacke, robert.staacke@physik.uni-leipzig.de
 * @author Lukas Botsch, lukas.botsch@uni-leipzig.de
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "counter.h"


int Counter_GetCountingTime(int argc, char **argv, char **res, size_t *resLen)
{
	float countingTime;
  int result = rp_CounterGetCountingTime(&countingTime);
  if (RP_OK != result) {
    RP_LOG(LOG_ERR, "COUNTER:TIME? Failed to get counting time: %s.\n", rp_GetError(result));
		*resLen = 0;
		return 1;
  }

	*resLen = safe_sprintf(res, "%g", countingTime);
	if (*resLen < 0) {
		RP_LOG(LOG_ERR, "COUNTER:TIME? Failed to construct response. Out of memory?\n");
    *res = NULL;
    *resLen = 0;
		return 1;
	}
  return 0;
}

int Counter_SetCountingTime(int argc, char **argv, char **res, size_t *resLen)
{
  *res = NULL;
  *resLen = 0;

	float countingTime;
	if (argc < 1) {
		RP_LOG(LOG_ERR, "COUNTER:TIME is missing first argument.\n");
		return 1;
	}
	countingTime = atof(argv[0]);
	if (countingTime == 0.0) {
		RP_LOG(LOG_ERR, "COUNTER:TIME invalid first argument: %s.\n", argv[0]);
    return 1;
	}
  int result = rp_CounterSetCountingTime(countingTime);
  if (RP_OK != result) {
    RP_LOG(LOG_ERR, "COUNTER:TIME Failed to set counting time: %s.\n", rp_GetError(result));
    return 1;
  }
	return 0;
}


int Counter_Count(int argc, char **argv, char **res, size_t *resLen)
{
	uint32_t counts[RP_COUNTER_NUM_COUNTERS];

	int result = rp_CounterWaitForState(0/* 0 = idle state, see api/rpbase/src/counter.h */);
	if (RP_OK != result) {
		RP_LOG(LOG_ERR, "COUNTER:COUNT? Failed waiting for idle state: %s.\n", rp_GetError(result));
		return 1;
	}
	result = rp_CounterCountSingle(counts);
	if (RP_OK != result) {
		RP_LOG(LOG_ERR, "COUNTER:COUNT? Failed counting: %s.\n", rp_GetError(result));
		return 1;
	}

	*resLen = 0;
	for (int i = 0; i < RP_COUNTER_NUM_COUNTERS; i++) {
		char *cnt = NULL;
		int l;
		if (i == RP_COUNTER_NUM_COUNTERS-1)
			l = safe_sprintf(&cnt, "%u", counts[i]);
		else
			l = safe_sprintf(&cnt, "%u,", counts[i]);
		if (l < 0) {
			free(*res);
			return 1;
		}
    // Resize *res
    *res = realloc(*res, (*resLen+l+1)*sizeof(char));
    // append count
    memcpy(*res + *resLen, cnt, l+1);
		*resLen += l;
		free(cnt);
	}
	return 0;
}

int Counter_WaitAndReadAndStartCounting(int argc, char **argv, char **res, size_t *resLen)
{
	RP_LOG(LOG_INFO, "Begin: Command handler for COUNTER:WRSC?\n");
	
	uint32_t counts[RP_COUNTER_NUM_COUNTERS];

	RP_LOG(LOG_INFO, "Calling rp API function\n");
	int result = rp_CounterWaitAndReadAndStartCounting(counts);
	if (RP_OK != result) {
		RP_LOG(LOG_ERR, "COUNTER:WRSC? Failed counting: %s.\n", rp_GetError(result));
		return 1;
	}

	*resLen = 0;
	for (int i = 0; i < RP_COUNTER_NUM_COUNTERS; i++) {
		char *cnt = NULL;
		int l;
		
		if (i == RP_COUNTER_NUM_COUNTERS-1) {
			RP_LOG(LOG_INFO, "Calling safe_sprintf (w/o trailing comma)\n");
			RP_LOG(LOG_INFO, "Counts is: %u\n", counts[i]);
			l = safe_sprintf(&cnt, "%u", counts[i]);
		} else {
			RP_LOG(LOG_INFO, "Calling safe_sprintf (with trailing comma)\n");
			RP_LOG(LOG_INFO, "Counts is: %u\n", counts[i]);
			l = safe_sprintf(&cnt, "%u,", counts[i]);
		}
		if (l < 0) {
			free(*res);
			return 1;
		}
		// Allocating *res
		if (i == 0) {
			RP_LOG(LOG_INFO, "Allocating res\n");
			*res = malloc((l+1)*sizeof(char));
		} else {
			RP_LOG(LOG_INFO, "Reallocating res\n");
			*res = realloc(*res, (*resLen+l+1)*sizeof(char));
		}
		// append count
		RP_LOG(LOG_INFO, "Memcpy count to res\n");
		memcpy(*res + *resLen, cnt, l+1);
		
		*resLen += l;
		RP_LOG(LOG_INFO, "free cnt\n");

		free(cnt);
	}
	RP_LOG(LOG_INFO, "End: Command handler for COUNTER:WRSC?\n");
	return 0;
}

