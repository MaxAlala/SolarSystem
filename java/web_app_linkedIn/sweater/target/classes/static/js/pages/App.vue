


<template>
    <v-app>
        <v-toolbar app>
            <v-toolbar-title >vse</v-toolbar-title>
            <v-spacer></v-spacer>
            <span v-if="profile">{{profile}} &nbsp</span>
            <a class="nav-link"  href="/main">snippets</a>
            <form method="post"  action="/logout" id="form-logout">
                <input type="hidden" name="_csrf" value="${_csrf.token}"/>
             <button type="submit" class="btn btn-success">&nbsp logout</button>
            </form>
        </v-toolbar>

             <v-content>
            <v-container v-if="!profile">
                Необходимо авторизоваться через
                <a href="/login">Google</a>
            </v-container>
            <v-container v-if="profile">
                <messages-list />
            </v-container>
        </v-content>
    </v-app>
</template>

<script>
    import { mapState, mapMutations } from 'vuex'
    import MessagesList from 'messages/MessageList.vue'
    import { addHandler } from 'util/ws'
    import { getIndex } from 'util/collections'
    // var messageApi = Vue.resource('/message{/id}');
    // this.$resource().get()
    export default {
        components: {
            MessagesList
        },
        computed: mapState(['profile']),
        methods: mapMutations(['addMessageMutation', 'updateMessageMutation', 'removeMessageMutation']),

        created() {
            addHandler(data => {
                if (data.objectType === 'MESSAGE') {
//                     const index = this.messages.findIndex(item => item.id === data.body.id)
// console.log(index);
                    switch (data.eventType) {
                        case 'CREATE':
                            this.addMessageMutation(data.body)
                        case 'UPDATE':
                            this.updateMessageMutation(data.body)

                            break
                        case 'REMOVE':
                            // if (index > -1){
                            //     this.messages.splice(index, 1);
                            // }
                            this.removeMessageMutation(data.body)

                            break
                        default:
                            console.error(`Looks like the event type if unknown "${data.eventType}"`)
                    }
                } else {
                    console.error(`Looks like the object type if unknown "${data.objectType}"`)
                }
            })

                    // this.$resource('/message').get().then(result =>
                    //     result.json().then(data =>
                    //         data.forEach(message => this.messages.push(message))
                    //     )
                    // )

        },
        // data() {
        //     return {
        //         messages: [],
        //         profile: profile
        //     }
        // }

    }
</script>

<style>

</style>
