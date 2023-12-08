
import requests
import json

# Replace with your personal access token
token = "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"


# Define the headers for the API request
headers = {
  "Authorization": f"Bearer {token}",
  "Content-Type": "application/json"
}

#API endpoint
url = "https://api.github.com/graphql"

query = """
query ($cursor: String) {
 repository(
  owner:"PolusAI",
  name:"nyxus"
 ) {
  pullRequests(
    states: MERGED,
    first: 100,
    after: $cursor,
    orderBy: {
      direction:DESC,
      field: UPDATED_AT
    }
  ) {
    totalCount
    nodes {
      ... on PullRequest {
        mergedAt
        createdAt
        title
      }
    }
    pageInfo {
      hasNextPage,
      endCursor
    }
  }
 }
}
"""


cursor = None
while True:
   # Variables for the query
   variables = {
       "cursor": cursor
   }

   # POST request to the GitHub API
   response = requests.post(url, headers=headers, json={"query": query, "variables": variables})

   # Parse the response
   data = response.json()

   with open('response.json', 'a') as f:
       json.dump(data, f, indent=4)

   # Check if there are more pages
   if not data["data"]["repository"]["pullRequests"]["pageInfo"]["hasNextPage"]:
       break

   # Update the cursor to next request
   cursor = data["data"]["repository"]["pullRequests"]["pageInfo"]["endCursor"]

# Create a session
session = requests.Session()

# Use the session to send the POST request
response = session.post(url, headers=headers, json={"query": query, "variables": variables})


