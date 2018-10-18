#include <iostream>

int main()
{
    const float cpuTime = 39.4f;
    const float diskTime[4] = { 77.1f, 123.8f, 80.4f, 235.f };
    float diskQueue[4] = { 0.0f };
    float timeLimit = 20000.0f; // 20 sec
    float totalTimeElapsed = 0;
    int numberOfDownloads = 0;
    int totalDownloads = 0;
    int mostDrivesInUse = 0;

    while (totalTimeElapsed < timeLimit - cpuTime)
    {
        totalTimeElapsed += cpuTime;
        totalDownloads++;
        // Removing elapsed time
        for (int i = 0; i < 4; i++)
        {
            diskQueue[i] -= cpuTime;
            if (diskQueue[i] <= 0.0f)
            {
                diskQueue[i] = 0.0f;
            }
        }

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
        numberOfDownloads++;

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

        std::cout << "\n####################################\n"
                  << "Drives in use: " << drivesInUse << "\n"
                  << "Drive queues:\n"
                  << "Disk 1: " << diskQueue[0] << "ms.\n"
                  << "Disk 2: " << diskQueue[1] << "ms.\n"
                  << "Disk 3: " << diskQueue[2] << "ms.\n"
                  << "Disk 4: " << diskQueue[3] << "ms.\n"
                  << "####################################\n";
    }

    // Moves time forward to the deadline and removes downloads still in progress from final result
    int drivesInUse = 4;
    for (int i = 0; i < 4; i++)
    {
        diskQueue[i] -= (timeLimit - totalTimeElapsed);
        if (diskQueue[i] <= 0.0f)
        {
            drivesInUse--;
            diskQueue[i] = 0.0f;
        }
    }
    totalDownloads -= drivesInUse;

    std::cout << "\nDone, elapsed time: " << timeLimit << "ms. Downloads finished: " << totalDownloads << ". Most drives in use at a time: " << mostDrivesInUse << ".\n"
              << "####################################\n"
              << "Queues at deadline:\n"
              << "Disk 1: " << diskQueue[0] << "ms.\n"
              << "Disk 2: " << diskQueue[1] << "ms.\n"
              << "Disk 3: " << diskQueue[2] << "ms.\n"
              << "Disk 4: " << diskQueue[3] << "ms.\n"
              << "####################################\n";
    return 0;
}