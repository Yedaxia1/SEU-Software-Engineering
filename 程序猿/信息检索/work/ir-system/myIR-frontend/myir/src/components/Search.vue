<template>
  <div id="wapper">
    <div id="title">My IR System</div>
    <div id="search-box">
      <el-input placeholder="请输入查询内容" v-model="query">
        <template #append>
          <el-button @click="doQuery" icon="el-icon-search"></el-button>
        </template>
      </el-input>
    </div>
    <div id="choice-box">
      <div style="margin-bottom: 8px">
        <span class="remind-text">搜索模型:</span>
        <el-radio v-model="type" label="0">boolean-model</el-radio>
        <el-radio v-model="type" label="1">vector-model</el-radio>
        <el-radio v-model="type" label="2">prob-model</el-radio>
      </div>
      <div v-if="type == '0'">
        <span class="remind-text">权重方式选择:</span>
        <el-radio v-model="booleanType" label="0">tf-idf</el-radio>
        <el-radio v-model="booleanType" label="1">wf-idf</el-radio>
      </div>
      <div v-else-if="type == '1'">
        <div style="margin-bottom: 10px">
          <span class="remind-text">查询tf选项：</span>
          <el-select
            size="small"
            style="margin-right: 10px"
            v-model="queryTfType"
            placeholder="请选择"
          >
            <el-option
              v-for="item in tfOpts"
              :key="item.value"
              :label="item.label"
              :value="item.value"
            >
            </el-option>
          </el-select>
          <span class="remind-text">查询document选项：</span>
          <el-select
            size="small"
            style="margin-right: 10px"
            v-model="queryDocType"
            placeholder="请选择"
          >
            <el-option
              v-for="item in docOpts"
              :key="item.value"
              :label="item.label"
              :value="item.value"
            >
            </el-option>
          </el-select>
        </div>
        <div>
          <span class="remind-text">文档tf选项：</span>
          <el-select
            size="small"
            style="margin-right: 10px"
            v-model="docTfType"
            placeholder="请选择"
          >
            <el-option
              v-for="item in tfOpts"
              :key="item.value"
              :label="item.label"
              :value="item.value"
            >
            </el-option>
          </el-select>
          <span class="remind-text">文档document选项：</span>
          <el-select
            size="small"
            style="margin-right: 10px"
            v-model="docDocType"
            placeholder="请选择"
          >
            <el-option
              v-for="item in docOpts"
              :key="item.value"
              :label="item.label"
              :value="item.value"
            >
            </el-option>
          </el-select>
          <span class="remind-text">文档norm选项：</span>
          <el-select
            size="small"
            style="margin-right: 10px"
            v-model="docNormType"
            placeholder="请选择"
          >
            <el-option
              v-for="item in normOpts"
              :key="item.value"
              :label="item.label"
              :value="item.value"
            >
            </el-option>
          </el-select>
        </div>
      </div>
      <div v-else-if="type == '2'">
        <span class="remind-text">搜索方式选择:</span>
        <el-radio v-model="probType" label="0">BIM</el-radio>
        <el-radio v-model="probType" label="1">MLE</el-radio>
        <el-slider
          v-if="probType == '1'"
          v-model="lambda"
          max="1"
          step="0.01"
          show-input
        />
      </div>
    </div>
    <div id="result-box">
      <el-empty v-if="empty" description="无结果"></el-empty>
      <div v-else id="result-wapper">
        <p style="font-size: 15px">{{ msg }}</p>
        <el-card
          v-for="(item, index) in respond"
          :key="index"
          style="margin-bottom: 12px"
        >
          <el-link :href="item.url" target="_blank"
            ><a class="poem-title">{{ item.title }}</a></el-link
          >
          <p class="poem-author">{{ item.author }}</p>
          <p class="poem-body">{{ item.body }}</p>
          <p class="bottom-tip">本篇文档得分：{{ item.score }}</p>
        </el-card>
      </div>
    </div>
  </div>
</template>

<script>
import axios from "axios";
import { ElMessage } from "element-plus";

export default {
  data() {
    return {
      query: "",
      empty: true,
      msg: "",
      type: "0",
      booleanType: "0",
      probType: "0",
      lambda: 0,
      respond: [],
      tfOpts: [
        { label: "Nature", value: 0 },
        { label: "log", value: 1 },
        { label: "augmented", value: 2 },
        { label: "boolean", value: 3 },
      ],
      docOpts: [
        { label: "None", value: 0 },
        { label: "idf", value: 1 },
        { label: "prob-idf", value: 2 },
      ],
      normOpts: [
        { label: "None", value: 0 },
        { label: "L2 Norm", value: 1 },
      ],
      queryTfType: 0,
      queryDocType: 0,
      docTfType: 0,
      docDocType: 0,
      docNormType: 0,
    };
  },
  methods: {
    doQuery() {
      var str = this.query.trim();
      if (str == "") {
        ElMessage("输入不能为空");
        return;
      }
      if (this.type == "0") {
        this.doBooleanQuery(str);
      } else if (this.type == "1") {
        this.doVectorQuery(str);
      } else if (this.type == "2") {
        this.doProbQuery(str);
      }
    },
    doBooleanQuery(str) {
      axios({
        url: "http://127.0.0.1:18000/boolean/query",
        method: "GET",
        params: {
          query: str,
          type: parseInt(this.booleanType),
        },
      }).then(this.handleSendSuccess, this.handleSendError);
    },
    doVectorQuery(str) {
      var queryTfType = this.queryTfType;
      var queryDocType = this.queryDocType;
      var docTfType = this.docTfType;
      var docDocType = this.docDocType;
      var docNormType = this.docNormType;
      axios({
        url: "http://127.0.0.1:18000/vector/query",
        method: "GET",
        params: {
          query: str,
          queryTfType: queryTfType,
          queryDocType: queryDocType,
          docTfType: docTfType,
          docDocType: docDocType,
          docNormType: docNormType,
        },
      }).then(this.handleSendSuccess, this.handleSendError);
    },
    doProbQuery(str) {
      console.log(str);
      console.log(this.probType);
      var conf = undefined;
      if (this.probType == "0") {
        conf = {
          url: "http://127.0.0.1:18000/prob/bim/query",
          method: "GET",
          params: {
            query: str,
          },
        };
      } else {
        conf = {
          url: "http://127.0.0.1:18000/prob/mle/query",
          method: "GET",
          params: {
            query: str,
            lambda: this.lambda,
          },
        };
      }
      axios(conf).then(this.handleSendSuccess, this.handleSendError);
    },
    handleSendSuccess(response) {
      var code = response.data.code;
      if (code != 200) {
        ElMessage.error(response.data.msg);
        this.respond = [];
        this.empty = true;
      } else {
        this.msg = response.data.msg;
        this.respond = response.data.data;
        this.empty = this.respond.length == 0;
      }
    },
    handleSendError(error) {
      console.log(error.message);
      ElMessage.error("出错了！请稍后再试~");
    },
  },
};
</script>

<style>
#wapper {
  padding: 5vh 15vw 5vh 15vw;
}

#title {
  text-align: center;
  font-size: 30px;
  font-weight: bold;
  margin-bottom: 8px;
}

#search-box {
  height: 50px;
  line-height: 50px;
  display: flex;
  justify-content: space-around;
  padding: 5px;
  margin-bottom: 8px;
}

#choice-box {
  padding-left: 5px;
  padding-right: 5px;
  margin-bottom: 8px;
}

#result-box {
  padding: 5px;
}

.poem-title {
  font-size: 25px;
  font-weight: bold;
}

.poem-author {
  font-size: 15px;
  color: gray;
}

.poem-body {
  font-size: 18px;
}

.bottom-tip {
  font-size: 8px;
  color: gray;
}

.remind-text {
  margin-right: 8px;
  font-size: 13px;
  color: gray;
}
</style>
