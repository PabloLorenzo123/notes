# News Feed System Design
Design a news feed

## Functional Requirements
- Create Posts
- Follow Someone
- Friend Someone
- Get Feed
- Getting Personalized Feed

## Non-Functional Requirements
- Low latency.
- Consistency (eventual) < High Availability, [read](https://www.designgurus.io/blog/system-design-interview-basics-cap-vs-pacelc?gad_source=1&gad_campaignid=23163907085&gbraid=0AAAAADME9yoiAkwluLhhI13tzb3TpEMde&gclid=CjwKCAjw9NjRBhATEiwA_p2J8WU3smJOHe91C48R5NPnelyxCTr5aGlNRBpqRHtnV480LqAh6DfFbBoCfDsQAvD_BwE).
- 5 Billion Users.
- Follow infinite.

## API
POST /potContent
{

}

GET /feed?pointer={}&pageSize={}
{
    POST: []
    pointer:
}

PUT /follow/[usrdId] - Idempotent
{}

## Schema
USER
POST
FOLLOW

## HLD
