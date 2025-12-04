#include <stdint.h>
#define THRESHOLD_1 5
#define N 5 // imciu skaicius stebimame laiko intervale
#define K 3 // kanalu skaicius iš užduoties

uint8_t Samples[K][N] = {
    { 1, 2, 3, 4, 5 },  // kanalas 0
    { 10,  0,  20,  50,  0  },  // kanalas 1
    { 255,  255, 255,  255, 255  }   // kanalas 2
};

int SkaiciuotiVidurkioKirtimusKanalui(const uint8_t Samples[][N], int kanalas)
{
    // 1. Vidurkis
    uint32_t sum = 0;
    for (int i = 0; i < N; i++)
        sum += Samples[kanalas][i];

    float avg = (float)sum / (float)N;

    // 2. Pradinis ženklas
    int prev_sign;
    if      (Samples[kanalas][0] > avg) prev_sign =  1;
    else if (Samples[kanalas][0] < avg) prev_sign = -1;
    else                                prev_sign =  0;

    int crossings = 0;

    // 3. Kirtimai
    for (int i = 1; i < N; i++)
    {
        int curr_sign;
        if      (Samples[kanalas][i] > avg) curr_sign =  1;
        else if (Samples[kanalas][i] < avg) curr_sign = -1;
        else                                curr_sign =  0;

        if (prev_sign != 0 && curr_sign != 0 && prev_sign != curr_sign)
            crossings++;

        if (curr_sign != 0)
            prev_sign = curr_sign;
    }

    return crossings;
}


int Pozymis[K];  // vienas požymis kiekvienam kanalui

int main(void)
{
    for (int ch = 0; ch < K; ch++)
    {
        Pozymis[ch] = SkaiciuotiVidurkioKirtimusKanalui(Samples, ch);
    }
}