import { sveltekit } from '@sveltejs/kit/vite';

const config = {
	plugins: [sveltekit()],
    server: {
        proxy: {
            "/api": {
                target: "https://api.krome0.com",
                changeOrigin: true,
                secure: false,
                rewrite: (path) => path.replace(/^\/api/, "")
            }
        }
    }
};

export default config;
