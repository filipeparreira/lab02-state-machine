#include "Musicas.h"

// ==========================================
// ARRAYS DAS MÚSICAS
// ==========================================

// 1. Super Mario Bros (Tempo = 200)
const int mario_melody[] = {
  NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,8, NOTE_G5,4, REST,4, NOTE_G4,8, REST,4, 
  NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8, REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,
  NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8, REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,
  REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8, REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
  REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4, NOTE_C5,2, REST,2,
  REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8, REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
  REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4, NOTE_C5,2, REST,2,
  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4, NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8, REST,1, 
  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4, NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
  NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4, NOTE_G5,4, REST,4, NOTE_G4,4, REST,4, 
  NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8, REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,
  NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8, REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,
  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4, NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8, NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, 
  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4, NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8, NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4, NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8, NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, 
  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4, NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8, NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8, REST,1,
  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4, NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
  NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4, NOTE_G5,4, REST,4, NOTE_G4,4, REST,4, 
  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4, NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8, NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4, NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8, NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
  NOTE_C5,-4, NOTE_G4,-4, NOTE_E4,4, NOTE_A4,-8, NOTE_B4,-8, NOTE_A4,-8, NOTE_GS4,-8, NOTE_AS4,-8, NOTE_GS4,-8,
  NOTE_G4,8, NOTE_D4,8, NOTE_E4,-2
};

// 2. Mii Channel (Tempo = 114)
const int mii_melody[] = {
  NOTE_FS4,8, REST,8, NOTE_A4,8, NOTE_CS5,8, REST,8,NOTE_A4,8, REST,8, NOTE_FS4,8, NOTE_D4,8, NOTE_D4,8, NOTE_D4,8, REST,8, REST,4, REST,8, NOTE_CS4,8,
  NOTE_D4,8, NOTE_FS4,8, NOTE_A4,8, NOTE_CS5,8, REST,8, NOTE_A4,8, REST,8, NOTE_F4,8, NOTE_E5,-4, NOTE_DS5,8, NOTE_D5,8, REST,8, REST,4,
  NOTE_GS4,8, REST,8, NOTE_CS5,8, NOTE_FS4,8, REST,8,NOTE_CS5,8, REST,8, NOTE_GS4,8, REST,8, NOTE_CS5,8, NOTE_G4,8, NOTE_FS4,8, REST,8, NOTE_E4,8, REST,8,
  NOTE_E4,8, NOTE_E4,8, NOTE_E4,8, REST,8, REST,4, NOTE_E4,8, NOTE_E4,8, NOTE_E4,8, REST,8, REST,4, NOTE_DS4,8, NOTE_D4,8, 
  NOTE_CS4,8, REST,8, NOTE_A4,8, NOTE_CS5,8, REST,8,NOTE_A4,8, REST,8, NOTE_FS4,8, NOTE_D4,8, NOTE_D4,8, NOTE_D4,8, REST,8, NOTE_E5,8, NOTE_E5,8, NOTE_E5,8, REST,8,
  REST,8, NOTE_FS4,8, NOTE_A4,8, NOTE_CS5,8, REST,8, NOTE_A4,8, REST,8, NOTE_F4,8, NOTE_E5,2, NOTE_D5,8, REST,8, REST,4,
  NOTE_B4,8, NOTE_G4,8, NOTE_D4,8, NOTE_CS4,4, NOTE_B4,8, NOTE_G4,8, NOTE_CS4,8, NOTE_A4,8, NOTE_FS4,8, NOTE_C4,8, NOTE_B3,4, NOTE_F4,8, NOTE_D4,8, NOTE_B3,8,
  NOTE_E4,8, NOTE_E4,8, NOTE_E4,8, REST,4, REST,4, NOTE_AS4,4, NOTE_CS5,8, NOTE_D5,8, NOTE_FS5,8, NOTE_A5,8, REST,8, REST,4, 
  REST,2, NOTE_A3,4, NOTE_AS3,4, NOTE_A3,-4, NOTE_A3,8, NOTE_A3,2, REST,4, NOTE_A3,8, NOTE_AS3,8, NOTE_A3,8, NOTE_F4,4, NOTE_C4,8, NOTE_A3,-4, NOTE_A3,8, NOTE_A3,2,
  REST,2, NOTE_B3,4, NOTE_C4,4, NOTE_CS4,-4, NOTE_C4,8, NOTE_CS4,2, REST,4, NOTE_CS4,8, NOTE_C4,8, NOTE_CS4,8, NOTE_GS4,4, NOTE_DS4,8, NOTE_CS4,-4, NOTE_DS4,8, NOTE_B3,1,
  NOTE_E4,4, NOTE_E4,4, NOTE_E4,4, REST,8
};

// 3. Pacman (Tempo = 105)
const int pacman_melody[] = {
  NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16, NOTE_B5, 32, NOTE_FS5, -16, NOTE_DS5, 8, NOTE_C5, 16,
  NOTE_C6, 16, NOTE_G6, 16, NOTE_E6, 16, NOTE_C6, 32, NOTE_G6, -16, NOTE_E6, 8,
  NOTE_B4, 16,  NOTE_B5, 16,  NOTE_FS5, 16,   NOTE_DS5, 16,  NOTE_B5, 32, NOTE_FS5, -16, NOTE_DS5, 8,  NOTE_DS5, 32, NOTE_E5, 32,  NOTE_F5, 32,
  NOTE_F5, 32,  NOTE_FS5, 32,  NOTE_G5, 32,  NOTE_G5, 32, NOTE_GS5, 32,  NOTE_A5, 16, NOTE_B5, 8
};

// 4. Nokia Tune (Tempo = 180)
const int nokia_melody[] = {
  NOTE_E5, 8, NOTE_D5, 8, NOTE_FS4, 4, NOTE_GS4, 4, NOTE_CS5, 8, NOTE_B4, 8, NOTE_D4, 4, NOTE_E4, 4, 
  NOTE_B4, 8, NOTE_A4, 8, NOTE_CS4, 4, NOTE_E4, 4, NOTE_A4, 2
};

// 5. Tetris (Tempo = 144)
const int tetris_melody[] = {
  NOTE_E5, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_C5,8,  NOTE_B4,8, NOTE_A4, 4,  NOTE_A4,8,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, -4,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4, NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,4, REST,4,
  REST,8, NOTE_D5, 4,  NOTE_F5,8,  NOTE_A5,4,  NOTE_G5,8,  NOTE_F5,8, NOTE_E5, -4,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4, NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,4, REST, 4,
  NOTE_E5,2, NOTE_C5,2, NOTE_D5,2, NOTE_B4,2, NOTE_C5,2, NOTE_A4,2, NOTE_B4,1,
  NOTE_E5,2, NOTE_C5,2, NOTE_D5,2, NOTE_B4,2, NOTE_C5,4, NOTE_E5,4, NOTE_A5,2, NOTE_GS5,1,
  NOTE_E5, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_C5,8,  NOTE_B4,8, NOTE_A4, 4,  NOTE_A4,8,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, -4,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4, NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,4, REST,4,
  REST,8, NOTE_D5, 4,  NOTE_F5,8,  NOTE_A5,4,  NOTE_G5,8,  NOTE_F5,8, REST,8, NOTE_E5, 4,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  REST,8, NOTE_B4, 4,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4, REST,8, NOTE_C5, 4,  NOTE_A4,8,  NOTE_A4,4, REST, 4
};


// ==========================================
// CONSTRUTOR
// ==========================================
Musicas::Musicas(int pino) {
    pinoBuzzer = pino;
    pinMode(pinoBuzzer, OUTPUT);
    
    musicaAtiva = 0;
    tempoAnterior = 0;
    indiceNota = 0;
    aguardandoPausa = false;
}

void Musicas::pararBuzzer() {
    noTone(pinoBuzzer);
    musicaAtiva = 0; 
}

void Musicas::iniciarMusica(int numeroMusica) {
    if (musicaAtiva == numeroMusica) return; 

    musicaAtiva = numeroMusica;
    indiceNota = 0;
    aguardandoPausa = false;
    tempoAnterior = millis();
    int tempoBPM = 100;

    // Configura os ponteiros e o BPM de acordo com a música
    switch (numeroMusica) {
        case 1: // Super Mario Bros
            melodiaAtual = mario_melody;
            tamanhoMusicaAtual = sizeof(mario_melody) / sizeof(mario_melody[0]);
            tempoBPM = 200;
            break;
        case 2: // Mii Channel
            melodiaAtual = mii_melody;
            tamanhoMusicaAtual = sizeof(mii_melody) / sizeof(mii_melody[0]);
            tempoBPM = 114;
            break;
        case 3: // Pacman
            melodiaAtual = pacman_melody;
            tamanhoMusicaAtual = sizeof(pacman_melody) / sizeof(pacman_melody[0]);
            tempoBPM = 105;
            break;
        case 4: // Nokia Tune
            melodiaAtual = nokia_melody;
            tamanhoMusicaAtual = sizeof(nokia_melody) / sizeof(nokia_melody[0]);
            tempoBPM = 180;
            break;
        case 5: // Tetris
            melodiaAtual = tetris_melody;
            tamanhoMusicaAtual = sizeof(tetris_melody) / sizeof(tetris_melody[0]);
            tempoBPM = 144;
            break;
        default:
            pararBuzzer();
            return;
    }

    // Calcula a duração de uma nota inteira em ms com base no tempo da música
    wholenote = (60000L * 4L) / tempoBPM;
    duracaoAtual = 0; 
}

// ==========================================
// MÁQUINA DE ESTADOS DO BUZZER (NON-BLOCKING)
// ==========================================
void Musicas::atualizar() {
    if (musicaAtiva == 0) return; 

    unsigned long tempoAtual = millis();

    // Verifica se já passou o tempo da nota atual ou da pausa
    if (tempoAtual - tempoAnterior >= duracaoAtual) {
        tempoAnterior = tempoAtual; 

        if (!aguardandoPausa) {
            // --- ESTADO 1: TOCAR A NOTA ---
            
            // Fim da música - Reseta para tocar em Loop infinito
            if (indiceNota >= tamanhoMusicaAtual) {
                indiceNota = 0; 
            }

            int notaMidi = melodiaAtual[indiceNota];
            int divider = melodiaAtual[indiceNota + 1];
            int noteDuration = 0;

            // Lógica original de cálculo de duração
            if (divider > 0) {
                noteDuration = wholenote / divider;
            } else if (divider < 0) {
                // Notas pontuadas são representadas com durações negativas
                noteDuration = wholenote / abs(divider);
                noteDuration *= 1.5; 
            }

            // A nota toca por 90% do tempo. Os 10% finais são de silêncio (separação das notas)
            duracaoAtual = noteDuration * 0.9;
            duracaoPausa = noteDuration * 0.1; 

            if (notaMidi != REST) {
                tone(pinoBuzzer, notaMidi); // Toca continuamente, a máquina de estados desligará depois
            } else {
                noTone(pinoBuzzer);
            }

            aguardandoPausa = true;       
            
        } else {
            // --- ESTADO 2: PAUSA ENTRE NOTAS (Silêncio de 10%) ---
            
            noTone(pinoBuzzer); 
            duracaoAtual = duracaoPausa; // O tempo de espera agora é o tempo da pausa
            aguardandoPausa = false; 
            
            // Pula 2 índices, pois o array intercala [NOTA, DURACAO, NOTA, DURACAO...]
            indiceNota += 2; 
        }
    }
}