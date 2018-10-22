#include <iostream>

int main()
{
    const int cpus = 2;
    const float cpuTime = 39.4f;
    const float diskTime[4] = { 77.1f, 123.8f, 80.4f, 235.f };
    float diskQueue[4] = { 0.0f };
    float timeLimit = 20000.0f; // 20 sec
    float totalTimeElapsed = 0;
    int totalDownloads = 0;
    int mostDrivesInUse = 0;

    while (totalTimeElapsed < timeLimit - cpuTime)
    {
        totalTimeElapsed += cpuTime;
        // Removing elapsed time
        for (int i = 0; i < 4; i++)
        {
            diskQueue[i] -= cpuTime;
            if (diskQueue[i] <= 0.0f)
            {
                diskQueue[i] = 0.0f;
            }
        }
        for (int cpu = 0; cpu < cpus; cpu++)
        {
            totalDownloads++;

            // Adding the next download to the shortest queue queue
            int smallestQueue = 0;
            for (int i = 1; i < 4; i++)
            {
                if (diskQueue[i] < diskQueue[smallestQueue])
                {
                    smallestQueue = i;
                }
            }
            diskQueue[smallestQueue] += diskTime[smallestQueue];
        }
        // Checking number of drives in use
        int drivesInUse = 4;
        for (int i = 0; i < 4; i++)
        {
            if (diskQueue[i] <= 0.0f)
            {
                drivesInUse--;
            }
        }
        if (drivesInUse > mostDrivesInUse)
        {
            mostDrivesInUse = drivesInUse;
        }

        //std::cout << "\n####################################\n"
        //    << "Drives in use: " << drivesInUse << "\n"
        //    << "Drive queues:\n"
        //    << "Disk 1: " << diskQueue[0] << "ms.\n"
        //    << "Disk 2: " << diskQueue[1] << "ms.\n"
        //    << "Disk 3: " << diskQueue[2] << "ms.\n"
        //    << "Disk 4: " << diskQueue[3] << "ms.\n"
        //    << "####################################\n";
    }

    // Removes downloads still in progress from final result
    for (int i = 0; i < 4; i++)
    {
        // Moves time forward to the deadline
        diskQueue[i] -= (timeLimit - totalTimeElapsed);
        while (diskQueue[i] > 0.0f)
        {
            diskQueue[i] -= diskTime[i];
            totalDownloads--;
        }
        diskQueue[i] = 0.0f;
    }

    std::cout << "\nDone.\n"
              << "####################################\n"
              << "Elapsed time : " << timeLimit << "ms.\n"
              << "Downloads finished : " << totalDownloads << ".\n"
              << "Most drives in use at a time : " << mostDrivesInUse << ".\n"
              << "Download rate: " << totalDownloads/(timeLimit/1000) << "tps.\n"
              << "####################################\n";
    return 0;
}