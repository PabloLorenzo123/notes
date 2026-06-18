# Status Codes
HTTP Status Codes
## 202 - Accepted

```202 Accepted``` means that the server has accepted the client's request, but has not yet completed the work requried to fulfill it.

It is commonly used when the server provide an inmediate response, because the requested operation is long-running, such as background jobs, batch processing, video transcoding, report generation, workflow orchestration.

The server typilically responds with:

```
HTTP/1.1 202 ACCEPTED
Location: /jobs/123
```

With the location header, the client can query to obtain the job/request status. this header tough is not required, these endpoints can be provided in a json in the response.

I've first seen this in a Azure Function Durable Function endpoint, a durable function is a function that orchestartes other functions following a fan-out/fan-in approach, it persists the job state, retries etc, example given is a batch policy emission where everything needs to be atomic. This endpoint returns a 202, with the job state, and one can query it using the uri in the location response header.

A common example is an Azure Durable Function HTTP endpoint. Durable Functions allow developers to orchestrate multiple functions using patterns such as Fan-Out/Fan-In, while automatically handling state persistence, retries, checkpoints, and recovery.

For example, a batch policy emission process may involve issuing hundreds of policies, validating data, generating documents, and sending notifications. Since this workflow can take a significant amount of time, the HTTP endpoint schedules the orchestration and immediately returns a 202 Accepted response.

The response contains an orchestration instance ID and status URLs that the client can use to monitor progress:

{
    "id": "instance-123",
    "statusQueryGetUri": "...",
    "terminatePostUri": "...",
    "sendEventPostUri": "..."
}

The orchestration continues executing in the background while the client periodically queries the status endpoint until the workflow reaches a terminal state such as Completed, Failed, or Terminated.