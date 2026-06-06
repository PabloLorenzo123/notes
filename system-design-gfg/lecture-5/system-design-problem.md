# Uber For Driver
The core problem uber for driver, uber eats, swiggy, is to find the closest available person to handle a client's request.

## Functional Requirements
- Drivers should be able to accept rides.
- The application should show the fastest route from source to the destination of the trip.
- Passengers can be rated.
- Drivers should only see the available rides for trips they can realistically complete based on available drivers supply per area.


## Non-Functional Requirements.

It seems that the actual system is the Uber App.

# Uber

## Functional Requirements
1. Trip fare estimation.
2. Rider should get a ride on estimated fare.
3. Matching the nearby or available driver.
4. Driver should accept/decline the request.
5. Driver should be able to navigate from source to destination.

## Non Functional Requirements:
1. Matching should be quick.
2. Strong Consistency: should not match mu
3. High Availability.
4. Scalable.
5. Handle High Throughput.

## API DESIGN

### POST /fare
```
{
    source,
    destination
}
```

### GET /ride/{fareId}/drivers

### POST /driverlocation

### POST /ride/id