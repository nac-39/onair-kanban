/**
 * Welcome to Cloudflare Workers! This is your first worker.
 *
 * - Run "npm run dev" in your terminal to start a development server
 * - Open a browser tab at http://localhost:8787/ to see your worker in action
 * - Run "npm run deploy" to publish your worker
 *
 * Learn more at https://developers.cloudflare.com/workers/
 */

interface QueryParams {
  [key: string]: string;
}

export interface Env {
  STORE_KV: KVNamespace;
}


export default {
  async fetch(request: Request, env: Env, ctx: ExecutionContext) {
    const url = new URL(request.url);
    const paths = url.pathname.split("/");
    const searchParams = url.searchParams;
    const queryParams: QueryParams = {}

    // クエリパラメータを抜き出す
    for (const [k, v] of searchParams) queryParams[k] = v;

    // パスごとに処理を分岐
    switch (`${request.method} /${paths[1]}`) {
      case "GET /status":
        const statusRes = await env.STORE_KV.get("status");
        return new Response(statusRes)
      case "POST /update":
        const status = queryParams["status"];
        await env.STORE_KV.put("status", status);
        return new Response(status)
      default:
        throw new Error(`${request.method} /${paths[1]} is not supported.`);
    }
  },
};
