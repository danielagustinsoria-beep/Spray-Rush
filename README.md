# Trabajo Final PEV 2 - Spray Rush
**Alumno:** Daniel Agustín Soria | **Legajo:** 41.735.523 | **Modo:** Idea Propia | **Versión de Unreal: [UE 5.6.1]
---
## Reglas y Mecánica Principal
- **Mecánica:** - El jugador deberá moverse por el mapa con su skate, recolectar latas de pintura y colorear grafitis, se pueden robar los sprays del otro jugador.
- **Cómo se gana:** Cómo se gana: El primero en pintar 3 paredes gana la partida. Si se agota el tiempo de la ronda (3 minutos), gana quien haya pintado más paredes; si hay empate, no hay ganador. La pantalla final muestra Victoria, Derrota o Empate a cada jugador.
---
## Ficha Técnica de Red
Ficha Técnica de Red
RepNotify: bIsPaintable en APaintableGraffiti -> al cambiar, todos los clientes (y el host) aplican el color del jugador a la pared pintada.

Server RPC: Server_TrySteal en ADeathmatchPlayerController -> el servidor valida que la partida esté en curso, que haya una lata de otro jugador dentro del alcance (StealRange), que no esté en cooldown y que el jugador no lleve ya una lata.

Client RPC: Client_ShowMessage en ADeathmatchPlayerController -> avisos directos a un solo jugador (por ejemplo "No tienes lata para pintar" o "¡Te robaron la lata!").

NetMulticast RPC: Multicast_PlayPaintFX en APaintableGraffiti -> efecto visual y sonido de pintura para todos los clientes.

HasAuthority: la recogida y el robo de latas, el pintado de paredes, el puntaje, la condición de victoria y el fin de partida se validan solo en el servidor.

Replicated: PaintColor (APaintableGraffiti), PaintedWalls, bHasCan y PlayerColor (ADeathmatchPlayerState), RemainingTime y WinnerPlayerState (ADeathmatchGameState).

Framework: ADeathmatchGameMode (reglas, inicio, timer y fin de partida), ADeathmatchGameState (tiempo restante y ganador; estado Lobby/Jugando/Fin mediante el MatchState), ADeathmatchPlayerState (paredes pintadas, lata equipada y color), ADeathmatchPlayerController (HUD e inputs) y ACharacter_J (personaje replicado).

---
## Cómo Probar el Proyecto
EN EL EDITOR: 
1. Abrir el mapa: `Content/PEV2/Maps/L_MainMenu`.
2. En Play (PIE): Number of Players = (hasta 4 jugadores) y `Net Mode = Play as Listen Server`.

EN LA BUILD:
1. En el menú principal, tocar botón "Local".
2. Un jugador hostea y se une automaticamente a la partida, tocar botón "Host".
3. Los demás jugadores ingresan la dirección IPv4 del host y presionan botón "Join".

Link a la build: https://drive.google.com/drive/folders/1e-gaWqG4cdSTmrgmuqcEzIlESaaBj_x7?usp=sharing
