<template>
    <v-layout align-space-around justify-start column>
        <message-form :messageAttr="message" />
        <message-row v-for="message in sortedMessages"
                     :key="message.id"
                     :message="message"
                     :editMessage="editMessage"

        />
    </v-layout>
</template>

<script>
    import MessageRow from 'messages/MessageRow.vue'
    import MessageForm from 'messages/MessageForm.vue'
    import { mapGetters } from 'vuex'

    export default {
        // props: ['messages'],
        components: {
            MessageRow,
            MessageForm
        },
        data() {
            return {
                message: null
            }
        },
        computed: mapGetters(['sortedMessages']),
        methods: {
            editMessage(message) {
                this.message = message
            },
            //
            // deleteMessage(message) {
            //     this.$resource('/message{/id}').remove({id: message.id}).then(result => {
            //         if (result.ok) {
            //             // console.log(this.messages.indexOf(message));
            //             // this.messages.splice(this.messages.indexOf(message), 1)
            //         }
            //     })
            // }
        }
    }
</script>

<style>

</style>
