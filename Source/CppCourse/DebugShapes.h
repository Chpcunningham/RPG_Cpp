#pragma once

#include "DrawDebugHelpers.h"

#define DRAW_SPHERE(Location, Color) if(GetWorld()) DrawDebugSphere(GetWorld(),Location, 25.f, 24, Color, false, 5.f);
#define DRAW_SPHERE_SINGLEFRAME(Location, Color) if(GetWorld()) DrawDebugSphere(GetWorld(),Location, 25.f, 24, Color, false, -1.f);

#define DRAW_LINE(StartLocation, EndLocation) if(GetWorld()) DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, true, -1.f, 0, 1.5f);
#define DRAW_LINE_SINGLEFRAME(StartLocation, EndLocation) if(GetWorld()) DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, -1.f, 0, 1.5f);
#define DRAW_POINT(StartLocation) if(GetWorld()) DrawDebugPoint(GetWorld(), StartLocation, 15.f, FColor::Red, true);
#define DRAW_POINT_SINGLEFRAME(StartLocation) if(GetWorld()) DrawDebugPoint(GetWorld(), StartLocation, 15.f, FColor::Red, false, -1.f);

#define DRAW_VECTOR(StartLocation, EndLocation) if(GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, true, -1.f, 0, 1.5f); \
		DrawDebugPoint(GetWorld(), EndLocation, 15.f, FColor::Cyan, true); \
	}
#define DRAW_VECTOR_SINGLEFRAME(StartLocation, EndLocation) if(GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, -1.f, 0, 1.5f); \
		DrawDebugPoint(GetWorld(), EndLocation, 15.f, FColor::Cyan, false, -1.f); \
	}

#define DRAW_CONE(Location, Color, Direction) if(GetWorld()) \
	{ \
		DrawDebugCone(GetWorld(), Location, Direction, 30.f, FMath::DegreesToRadians(30.f), FMath::DegreesToRadians(30.f), 12, Color, true); \
	}
#define DRAW_CONE_SINGLEFRAME(Location, Color, Direction) if(GetWorld()) \
	{ \
		DrawDebugCone(GetWorld(), Location, Direction, 30.f, FMath::DegreesToRadians(30.f), FMath::DegreesToRadians(30.f), 12, Color, false, -1.f); \
	}
