# Trabajo Final PEV 2 - Spray Rush
**Alumno:** Daniel Agustín Soria | **Legajo:** 41.735.523 | **Modo:** Idea Propia | **Versión de Unreal: [UE 5.6]
---
## Reglas y Mecánica Principal
- **Mecánica:** - El jugador deberá moverse por el mapa con su skate, recolectar latas de pintura y colorear grafitis.
- **Cómo se gana:** [El jugador debe colorear 3 grafitis antes que los demás].
---
## Ficha Técnica de Red
- **RepNotify:** `[Variable]` en `[Clase]` -> [Qué actualiza al cambiar].
- **Server RPC:** `Server_[Funcion]` en `[Clase]` -> [Validación en el servidor].
- **Client RPC:** `Client_[Funcion]` en `[Clase]` -> [Aviso directo a un cliente].
- **NetMulticast RPC:** `Multicast_[Funcion]` en `[Clase]` -> [VFX / Audio global a todos].
---
## Cómo Probar el Proyecto
1. Abrir el mapa: `Content/PEV2/Maps/L_GameArena`.
2. En Play (PIE): `Number of Players = 2` (o 4+) y `Net Mode = Play as Listen Server`.
