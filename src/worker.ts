/**
 * Welcome to Cloudflare Workers! This is your first worker.
 *
 * - Run "npm run dev" in your terminal to start a development server
 * - Open a browser tab at http://localhost:8787/ to see your worker in action
 * - Run "npm run deploy" to publish your worker
 *
 * Learn more at https://developers.cloudflare.com/workers/
 */


export default {
  async fetch(request, env, ctx) {
    const url = new URL(request.url);
    const paths = url.pathname.split("/");
    const searchParams = url.searchParams;
    const queryParams = {}

    // クエリパラメータを抜き出す
    for (const [k, v] of searchParams) queryParams[k] = v;

    // パスごとに処理を分岐
    switch (paths[1]) {
      case "status":
        return new Response("in_meeting")
      case "update":
        if (queryParams["status"] == "in_meeting") {
          console.log("update to in meeting")
        } else if (queryParams["status"] == "in_mute") {
          console.log("update to mute")
        }
        return new Response(queryParams["status"])
      default:
        throw new Error(`${request.method} is not supported.`);
    }
  },
};
