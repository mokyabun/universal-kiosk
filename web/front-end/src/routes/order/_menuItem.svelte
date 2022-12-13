<script>
    import { createEventDispatcher } from 'svelte'
    export let menu
    
    let checked = false
    let color = '#F7F7F7'
    const dispatch = createEventDispatcher()
    function selectMenu() {
        dispatch("selectMenu", {menu, checked})
        if (!checked) color = '#C7C7C7'
        else color = '#F7F7F7'
        checked = !checked;
    }
</script>

<button type="button" class="menu_button" on:click={selectMenu} style="background-color: {color}">
    <img src={menu.image} alt="menu_image" class="menu_img">
    <div class="menu_name">{menu.name}</div>
    <div class="menu_price">{menu.price}&#x20A9;</div>
</button>

<style>
    .menu_button {
        position: relative;
        border: none;
        display: inline-block;
        padding: 10px;
        border-radius: 25px;
        font-family: "paybooc-Light", sans-serif;
        text-decoration: none;
        font-weight: 600;
        transition: 0.25s;
        align-items: center;
    }
    
    .menu_button:hover {
        transform: scale(1.02);
    }
    
    .menu_name {
        font-weight: 700;
        font-size: 2.5vh;
        margin-top: 3px;
    }

    .menu_price {
        font-size: 1.5vh;
        margin-top: 3px;
        margin-bottom: 5px;
        text-align: center;
    }

    .menu_img {
        width: 18vh;
        margin-bottom: 5px;
    }
</style> 