<template>
    <v-layout row>
        <v-text-field
                label="New message"
                placeholder="Write something"
                v-model="text"
        ></v-text-field>
        <v-btn @click="save">
            Save
        </v-btn>
    </v-layout>
</template>

<script>
    // import { sendMessage } from 'util/ws'
    import { mapActions } from 'vuex'
    export default {
        props: [ 'messageAttr'],
        data() {
            return {
                text: '',
                id: ''
            }
        },
        watch: {
            messageAttr(newVal, oldVal) {
                this.text = newVal.text
                this.id = newVal.id
            }
        },
        methods: {
            ...mapActions(['addMessageAction', 'updateMessageAction']),

            save() {

                const message = {
                    id: this.id,
                    text: this.text
                }

                if (this.id) {
                    this.updateMessageAction(message)
                } else {
                    this.addMessageAction(message)
                }

                this.text = ''
                this.id = ''
            }
        }
    }
</script>

<style>

</style>
