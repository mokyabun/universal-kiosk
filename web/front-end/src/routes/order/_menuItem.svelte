<script>
    import { createEventDispatcher } from 'svelte'
    export let menu

    let checked = false
    const dispatch = createEventDispatcher()
    function selectMenu() {
        dispatch("selectMenu", {menu, checked})
        checked = !checked;
    }
</script>

<button type="button" class="menu_button" on:click={selectMenu}>
    <img src={menu.image} alt="menu_image" class="menu_img">
    <div class="menu_name">{menu.name}</div>
    <div class="menu_price">
        <div>&#x20A9;</div>
        <div id="price_{menu.id}">{menu.price}</div>
    </div>
</button>

<style>
    .menu_name {
        font-weight: 700;
        font-size: 2.5vh;
        margin-top: 3px;
    }

    .menu_price {
        font-size: 1.5vh;
        margin-top: 3px;
        margin-bottom: 5px;
        display: flex;
    }

    .menu_img {
        width: 18vh;
        margin-bottom: 5px;
    }
</style> 